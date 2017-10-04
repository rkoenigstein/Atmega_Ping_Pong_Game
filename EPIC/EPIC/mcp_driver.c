#include <avr/io.h>
#include <avr/interrupt.h>

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
	spi_MasterTransmit(RESET);
}

void mcp_init(void)
{
	mcp_reset();
}

void mcp_write(uint8_t address, char data)
{
	spi_MasterTransmit(WRITE);
	spi_MasterTransmit(address);
	spi_MasterTransmit(data);
}

char mcp_read(uint8_t address)
{
	spi_MasterTransmit(READ);
	spi_MasterTransmit(address);
	return spi_SlaveReceive();
}

char mcp_read_status(void)
{
	spi_MasterTransmit(READ_STATUS);
	return spi_SlaveReceive();
}

void mcp_bit_modify(char mask_byte, uint8_t reg_adr, char data )
{
	spi_MasterTransmit(BIT_MODIFY);
	spi_MasterTransmit(reg_adr);
	spi_MasterTransmit(mask_byte);
	spi_MasterTransmit(data);
}


void mcp_request_to_send (uint8_t out_buffer)
{
	spi_MasterTransmit(RTS||out_buffer);	
}
