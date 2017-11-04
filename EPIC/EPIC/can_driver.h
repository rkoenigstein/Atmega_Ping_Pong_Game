#ifndef CAN_DRIVER_H_
#define CAN_DRIVER_H_

#include <stdint.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include "mcp_driver.h"

typedef struct can_message
{
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
} can_message;

/* initialize CAN bus */
void can_init(void);

/* send message to CAN bus */
void can_message_send(can_message can_msg);

/* returns true if a bus error occured */
bool can_error(void);

/* returns true if CAN transmission finished */
bool can_transmit_complete(void);

/* returns received message from CAN bus */
can_message can_data_receive(void);

/* print CANSTAT and CANCRTL registers from MCP */
void printRegisters();

/* test CAN in loopback mode */
void CAN_test(void);

/* transmit test CAN msg */
void CAN_send_dummy(void);

#endif
