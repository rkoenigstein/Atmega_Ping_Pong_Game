
#ifndef MCP_DRIVER_H_
#define MCP_DRIVER_H_

//Reset MCP by SPI interface
void mcp_reset(void);

//Initialiye MCP
void mcp_init(void);

//Read data from MCP
uint8_t mcp_read(uint8_t address);

//Write data to MCP
void mcp_write(uint8_t address, char data);


//Read MCP status
uint8_t mcp_read_status(void);

//Modify data fitting bit mask in register of adress reg_adr
void mcp_bit_modify(uint8_t mask_byte, uint8_t reg_adr, uint8_t data);

//Select output buffer for CAN communication (USE TXB0/1/2 or NO_BUFFER)
void mcp_request_to_send (uint8_t out_buffer);


#endif