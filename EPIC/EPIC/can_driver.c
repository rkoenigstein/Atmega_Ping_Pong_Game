#include <avr/io.h>

#include "can_driver.h"
#include "mcp2515.h"
#include "spi_driver.h"
#include "uart_driver.h"
#include <stdio.h>
#define F_CPU 4915200 // Clock speed

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
	
	//BUFFER ONE WORKING!!!
	
	mcp_init();
		
	//turn off filters and rollover for receive buffer 0
	mcp_bit_modify(NO_FILTERS_AND_MASKS, MCP_RXB0CTRL , 0xFF);
	//enable interrupt for received message
	mcp_bit_modify(MCP_RX0IF, MCP_CANINTE, 0x00);
	
	//activate loopback mode on the MCP2515 for today
	mcp_bit_modify(MODE_MASK, MCP_CANCTRL, MODE_LOOPBACK);
		
	printf("BFPCTRL: 0x%02x\n", mcp_read(0x0C));

	//printf("CANINTE 0x%02x\n", mcp_read(MCP_CANINTE));
	
	//activate normal mode on the MCP2515 (only mode in which it can transmit CAN messages
	//mcp_bit_modify(MODE_MASK, MCP_CANCTRL, MODE_NORMAL);
	
	//enabling CAN interrupts
	cli();
	MCUCR |= (1<<ISC11);
	GICR |= (1<<INT0);
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
	
	printf("CANINTF.RX0IF: 0x%02x\n", mcp_read(MCP_CANINTF));
	
	printf("RXB0SIDH: 0x%02x\n", mcp_read(MCP_RXB0SIDH) );
	while(!msg_received_flag);
	//while(!(mcp_read(0x2c) & (1 | 2)));
	printf("jkslfgdfg\n");
	//read upper 8 bit of id
	can_msg.id = mcp_read(MCP_RXB0SIDH) << 5;
	//read lower 8 bit of id
	can_msg.id |= mcp_read(MCP_RXB0SIDL) >> 3;
	//read length of CAN data
	can_msg.length = mcp_read(MCP_RXB0DLC);
	//read CAN data
	for(uint8_t i = 0; i < can_msg.length; i++)
		can_msg.data[i] = mcp_read(MCP_RXB0D0+i); 
	msg_received_flag = 0;
	
	//allow new message to be received into the buffer
	//mcp_write(MCP_RX0IF, 0x00);
	mcp_bit_modify(MCP_RX0IF, MCP_CANINTF, 0x00);
	return can_msg;
}

void can_int_vect(void)
{
	
		
}

ISR(INT0_vect)
{
	printf("interrupted!\n");
	printf("CANINTF.RX0IF: 0x%02x\n", mcp_read(MCP_CANINTF));
	mcp_bit_modify(MCP_RX0IF, MCP_CANINTF, 0x00);
	msg_received_flag = 1;
}

void CAN_test(void)
{
	//activate loopback mode on the MCP2515 for today
	mcp_bit_modify(MODE_MASK, MCP_CANCTRL, MODE_LOOPBACK);

	//received CAN message
	can_message received_msg;

	//send CAN message 
	can_message can_msg = { .id = 1000, .length = 4, .data = {'a', 'c', 'A', '!'}};
	can_message_send(can_msg);
	_delay_ms(100);
	//receive CAN message
	received_msg = can_data_receive();
	
	printf("CAN id: %d, CAN data length: %d, CAN data: %c, %c, %c, %c\n", received_msg.id, received_msg.length, received_msg.data[0], received_msg.data[1], received_msg.data[2], received_msg.data[3]);
}

void printRegisters(void)
{
	uint8_t canstat = mcp_read(MCP_CANSTAT);
	printf("CANSTAT: 0x%02x\n", canstat);
	
	uint8_t canctrl = mcp_read(MCP_CANCTRL);
	printf("CANCTRL: 0x%02x\n", canctrl);
}