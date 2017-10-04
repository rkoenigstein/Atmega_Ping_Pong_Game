#include <avr/io.h>

#include "can_driver.h"
#include "mcp2515.h"

#define NO_FILTERS_AND_MASKS 0x01100000
#define TXREQ 0b00001000
#define TXERR 0b00010000
#define RTR_DATA_FRAME 0x0F

void can_init(void)
{
	
	//activate normal mode on the MCP2515 (only mode in which it can transmit CAN messages
	//mcp_bit_modify(MODE_MASK, MCP_CANCTRL, MODE_NORMAL);
	
	//turn off filters and rollover for receive buffer 1 
	mcp_bit_modify(NO_FILTERS_AND_MASKS, MCP_RXB0CTRL , 0xFF);
	
	//activate loopback mode on the MCP2515 for today
	mcp_bit_modify(MODE_MASK, MCP_CANCTRL, MODE_LOOPBACK);
	
	//enable interrupt for received message
	mcp_bit_modify(MCP_RX0IF, MCP_CANINTE, MCP_TX01_INT)
}

void can_message_send(can_message)
{
	if(can_transmit_complete())
	{
		mcp_write(MCP_TXB0SIDH, can_message.id >> 3);
		mcp_write(MCP_TXB0SIDL, can_message.id << 5);
		mcp_write(MCP_TXB0DLC, RTR_DATA_FRAME && can_message.length);
		
		for(uint8_t i = 0; i < can_message.length; i++)
			mcp_write(MCP_TXB0D0+i, can_message.data[i]);
		
		mcp_request_to_send(TXB0);
	}	
}

bool can_error(void)
{
	return TXERR && mcp_read(MCP_TXB0CTRL);
	
}

bool can_transmit_complete(void)
{
	return !(TXREQ && mcp_read(MCP_TXB0CTRL));
}

can_message can_data_receive(void)
{
	
	
}

void can_int_vect(void)
{
	
	
}