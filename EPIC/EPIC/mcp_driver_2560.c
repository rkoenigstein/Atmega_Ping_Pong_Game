#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000 // Clock speed

#include <util/delay.h>
#include "mcp_driver_2560.h"
#include "spi_driver_2560.h"
#include "uart_driver_2560.h"
#include "MCP2515.h"
#include <avr/io.h>

#define RESET			0b11000000
#define READ			0b00000011			
#define READ_RX_BUFFER	0b10010000
#define WRITE			0b00000010
#define LOAD_TX_BUFFER	0b01000000
#define RTS				0b10000000
#define READ_STATUS		0b10100000
#define RX_STATUS		0b10110000
#define BIT_MODIFY		0b00000101

#define SPI_SS DDB7

void mcp_reset(void)
{
	//select slave MCP2515
	PORTB &= ~(1 << SPI_SS);
	
	spi_MasterTransmit(RESET);
	
	//deselect slave MCP2515
	PORTB |= 1 << SPI_SS;
	_delay_ms(1);
	
	//Self-test
	volatile uint8_t canstat;
	canstat = mcp_read(MCP_CANSTAT);
	if ((canstat & MODE_MASK) != MODE_CONFIG) {
		printf("MCP2515 is NOT in configuration mode after reset!\n");
	}
}

void mcp_init(void)
{
	spi_init();
	mcp_reset();
}

void mcp_write(uint8_t address, char data)
{
	//select slave MCP2515
	PORTB &= ~(1 << SPI_SS);
	
	spi_MasterTransmit(WRITE);
	spi_MasterTransmit(address);
	spi_MasterTransmit(data);
	
	//deselect slave MCP2515
	PORTB |= 1 << SPI_SS;
}

uint8_t mcp_read(uint8_t address)
{
	//select slave MCP2515
	PORTB &= ~(1 << SPI_SS);
	
	spi_MasterTransmit(READ);
	spi_MasterTransmit(address);
	
	uint8_t received_char = spi_SlaveReceive();

	//deselect slave MCP2515
	PORTB |= 1 << SPI_SS;
	
	return received_char;
}

uint8_t mcp_read_status(void)
{
	//select slave MCP2515
	PORTB &= ~(1 << SPI_SS);
	
	spi_MasterTransmit(READ_STATUS);
	
	uint8_t received_char = spi_SlaveReceive();

	//deselect slave MCP2515
	PORTB |= 1 << SPI_SS;
		
	return received_char;
}

void mcp_bit_modify(uint8_t mask_byte, uint8_t reg_adr, uint8_t data )
{
	//select slave MCP2515
	PORTB &= ~(1 << SPI_SS);
	
	spi_MasterTransmit(BIT_MODIFY);
	spi_MasterTransmit(reg_adr);
	spi_MasterTransmit(mask_byte);
	spi_MasterTransmit(data);
	
	//deselect slave MCP2515
	PORTB |= 1 << SPI_SS;

}


void mcp_request_to_send (uint8_t out_buffer)
{
	//select slave MCP2515
	PORTB &= ~(1 << SPI_SS);
	
	spi_MasterTransmit(RTS|out_buffer);	
	
	//deselect slave MCP2515
	PORTB |= 1 << SPI_SS;
}