

#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#include <stdint.h>
#include <avr/io.h>

//Define MCP output buffers (for CAN)
#define NO_BUFFER 0
#define TXB0	0b00000001
#define	TXB1	0b10000010
#define	TXB2	0b10000100


//Initialize SPI communication
void spi_init(void);

//SPI transmit data to slave
void spi_MasterTransmit(char cData);

//SPI get data from slave
char spi_SlaveReceive(void);

//Read MCP status
char mcp_read_status(void);

//Modify data fitting bit mask in register of adress reg_adr
void mcp_bit_modify(char mask_byte, uint8_t reg_adr, char data);

//Select output buffer for CAN communication (USE TXB0/1/2 or NO_BUFFER)
void mcp_request_to_send (uint8_t out_buffer);


#endif