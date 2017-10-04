
#ifndef MCP_DRIVER_H_
#define MCP_DRIVER_H_

//Reset MCP by SPI interface
void mcp_reset(void);

//Initialiye MCP
void mcp_init(void);

//Read data from MCP
char mcp_read(uint8_t address);

//Write data to MCP
void mcp_write(uint8_t address, char data);



#endif