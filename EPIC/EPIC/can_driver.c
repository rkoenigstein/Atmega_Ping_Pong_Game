#include <avr/io.h>

#include "can_driver.h"
#include "mcp2515.h"
#include "spi_driver.h"
#include "uart_driver.h"
#include <stdio.h>
#ifdef ATMEGA2560
	#define F_CPU 16000000 // Clock speed
#else
	#define F_CPU 4915200 // Clock speed
#endif

#include <util/delay.h>

#define NO_FILTERS_AND_MASKS 0x01100000
#define TXREQ 0b00001000
#define TXERR 0b00010000
#define RTR_DATA_FRAME 0x0F
#define RX0IF 0x00
#define BFPCTRL 0x0C

volatile int msg_received_flag = 0;

void can_init(void)
{
	//initialize mcp
	mcp_init();

	//ensure to be in config mode
	mcp_write(MCP_CANCTRL, MODE_MASK & MODE_CONFIG);

	//turn off filters and rollover for receive buffer 0
	mcp_write(MCP_RXB0CTRL, NO_FILTERS_AND_MASKS);

	//enable interrupt for received message
	mcp_write(MCP_CANINTE, MCP_RX0IF);

	//activate normal mode on the MCP2515 (only mode in which it can transmit CAN messages)
	mcp_bit_modify(MODE_MASK, MCP_CANCTRL, MODE_NORMAL);

	//enable CAN interrupts on the MCU
	cli();
	#ifdef ATMEGA2560
		EICRB &= ~(1 << ISC31);
		EICRB &= ~(1 << ISC30);
		EIMSK |= (1 << INT3);
	#else
		MCUCR |= (1 << ISC11);
		GICR |= (1 << INT0);
	#endif
	sei();
}

void can_message_send(can_message can_msg)
{
	if(can_transmit_complete())
	{
		//write CAN msg ID to MCP2515
		mcp_write(MCP_TXB0SIDH, can_msg.id >> 3);
		mcp_write(MCP_TXB0SIDL, can_msg.id << 5);

		//write CAN data length to MCP2515
		mcp_write(MCP_TXB0DLC, RTR_DATA_FRAME & can_msg.length);

		//write CAN data to MCP2515
		for(uint8_t i = 0; i < can_msg.length; i++)
			mcp_write(MCP_TXB0D0+i, can_msg.data[i]);

		//send transmission request for transmitted CAN msg to MCP2515
		mcp_request_to_send(TXB0);
	}
	else
	{
		if(can_error())
			printf("CAN transmission error\n");
	}
}

bool can_error(void)
{
	//read CAN error status out of respective register
	return TXERR & mcp_read(MCP_TXB0CTRL);
}

bool can_transmit_complete(void)
{
	//check if transmission complete from status register
	return !(TXREQ & mcp_read(MCP_TXB0CTRL));
}

can_message can_data_receive(void)
{
	can_message can_msg;
	while(!msg_received_flag);

	//read upper 8 bit of id
	can_msg.id = mcp_read(MCP_RXB0SIDH) << 3;
	//read lower 8 bit of id
	can_msg.id |= mcp_read(MCP_RXB0SIDL) >> 5;
	//read length of CAN data
	can_msg.length = mcp_read(MCP_RXB0DLC);
	//read CAN data
	for(uint8_t i = 0; i < can_msg.length; i++)
		can_msg.data[i] = mcp_read(MCP_RXB0D0+i);
	msg_received_flag = 0;

	//allow new message to be received into the buffer
	mcp_write(MCP_CANINTF, MCP_RX0IF & 0x00);

	return can_msg;
}

//interrupt service routine clearing the receive buffer interrupt bit to receive next message
#ifdef ATMEGA2560
	ISR(INT3_vect)
	{
		//printf("interrupted CAN!\n");
		//clear interrupt bits for rx buffer 0
		mcp_write(MCP_CANINTF, MCP_RX0IF & 0x00);
		
		msg_received_flag = 1;
	}
#else
	ISR(INT0_vect)
	{
		//printf("Interrupted CAN!\n");
		//clear interrupt bits for rx buffer 0
		mcp_write(MCP_CANINTF, MCP_RX0IF & 0x00);

		msg_received_flag = 1;
	}	
#endif

void CAN_test(void)
{
	printf("Test CAN bus\n");
	//activate loopback mode on the MCP2515
	mcp_write(MCP_CANCTRL, MODE_MASK & MODE_LOOPBACK);

	//received CAN message
	can_message received_msg;

	//send CAN message
	can_message can_msg = { .id = 100, .length = 5, .data = {'i', 'C', 'A', 'N', 't'}};

	can_message_send(can_msg);
	_delay_ms(10);
	//receive CAN message
	received_msg = can_data_receive();

	printf("CAN id: %d, CAN data length: %d, CAN data: %c, %c, %c, %c, %c \n", received_msg.id, received_msg.length, received_msg.data[0], received_msg.data[1], received_msg.data[2], received_msg.data[3], received_msg.data[4]);
}

void CAN_send_dummy(void)
{
	//send CAN message
	can_message can_msg = { .id = 100, .length = 4, .data = {'i', 'C', 'A', 'N'}};

	can_message_send(can_msg);
	_delay_ms(10);
	printf("CAN msg sent -> CAN id: %d, CAN data length: %d, CAN data: %c, %c, %c, %c \n", can_msg.id, can_msg.length, can_msg.data[0], can_msg.data[1], can_msg.data[2], can_msg.data[3]);
}

void printRegisters(void)
{
	uint8_t canstat = mcp_read(MCP_CANSTAT);
	printf("CANSTAT: 0x%02x\n", canstat);

	uint8_t canctrl = mcp_read(MCP_CANCTRL);
	printf("CANCTRL: 0x%02x\n", canctrl);
}
