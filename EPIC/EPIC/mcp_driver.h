#ifndef MCP_DRIVER_H_
#define MCP_DRIVER_H_

/* resets MCP by SPI interface */
void mcp_reset(void);

/* initializes MCP by sending reset command and initializing SPI */
void mcp_init(void);

/* reads data from MCP */
uint8_t mcp_read(uint8_t address);

/* writes data to MCP */
void mcp_write(uint8_t address, uint8_t data);

/* reads MCP status */
uint8_t mcp_read_status(void);

/* modifies data fitting bit mask in register of adress reg_adr */
void mcp_bit_modify(uint8_t mask_byte, uint8_t reg_adr, uint8_t data);

/* selects output buffer for CAN communication (USE TXB0/1/2 or NO_BUFFER) */
void mcp_request_to_send (uint8_t out_buffer);

/* selects SPI slave */
void selectSlave(void);

/* deselects SPI slave */
void deselectSlave(void);

#endif
