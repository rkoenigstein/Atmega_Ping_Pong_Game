#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 4915200 // Clock speed

#include <util/delay.h>
#include "mcp_driver.h"
#include "spi_driver.h"

#define RESET			0b11000000
#define READ			0b00000011			
#define READ_RX_BUFFER	0b10010000
#define WRITE			0b00000010
#define LOAD_TX_BUFFER	0b01000000
#define RTS				0b10000000
#define READ_STATUS		0b10100000
#define RX_STATUS		0b10110000
#define BIT_MODIFY		0b00000101

void mcp_reset(void)
{
	//select slave MCP2515
	PORTB &= ~(1 << PB4);
	
	spi_MasterTransmit(RESET);
	
	//deselect slave MCP2515
	PORTB |= 1 << PB4;
	_delay_ms(1);
	
}

void mcp_init(void)
{
	spi_init();
	mcp_reset();
}

void mcp_write(uint8_t address, char data)
{
	//select slave MCP2515
	PORTB &= ~(1 << PB4);
	
	spi_MasterTransmit(WRITE);
	spi_MasterTransmit(address);
	spi_MasterTransmit(data);
	
	//deselect slave MCP2515
	PORTB |= 1 << PB4;
}

char mcp_read(uint8_t address)
{
	//select slave MCP2515
	PORTB &= ~(1 << PB4);
	
	spi_MasterTransmit(READ);
	spi_MasterTransmit(address);
	
	char received_char = spi_SlaveReceive();

	//deselect slave MCP2515
	PORTB |= 1 << PB4;
	
	return received_char;
}

char mcp_read_status(void)
{
	//select slave MCP2515
	PORTB &= ~(1 << PB4);
	
	spi_MasterTransmit(READ_STATUS);
	
	char received_char = spi_SlaveReceive();

	//deselect slave MCP2515
	PORTB |= 1 << PB4;
		
	return received_char;
}

void mcp_bit_modify(char mask_byte, uint8_t reg_adr, char data )
{
	//select slave MCP2515
	PORTB &= ~(1 << PB4);
	
	spi_MasterTransmit(BIT_MODIFY);
	spi_MasterTransmit(reg_adr);
	spi_MasterTransmit(mask_byte);
	spi_MasterTransmit(data);
	
	//deselect slave MCP2515
	PORTB |= 1 << PB4;

}


void mcp_request_to_send (uint8_t out_buffer)
{
	//select slave MCP2515
	PORTB &= ~(1 << PB4);
	
	spi_MasterTransmit(RTS|out_buffer);	
	
	//deselect slave MCP2515
	PORTB |= 1 << PB4;
}
