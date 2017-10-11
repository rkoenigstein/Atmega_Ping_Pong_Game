

#ifndef CAN_DRIVER_H_
#define CAN_DRIVER_H_

#include <stdint.h>
#include "mcp_driver.h"
#include <stdbool.h>
#include <avr/interrupt.h>

typedef struct can_message
{
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
	} can_message;

//initialize CAN bus
void can_init(void);

//send message to CAN bus
void can_message_send(can_message can_msg);

//returns true if a bus error occured
bool can_error(void);

//returns true if transmission finished
bool can_transmit_complete(void);

//receive message from CAN bus
can_message can_data_receive(void);

void can_int_vect(void);
void printRegisters();

//test CAN in loopback mode
void CAN_test(void);

#endif 