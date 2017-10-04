

#ifndef CAN_DRIVER_H_
#define CAN_DRIVER_H_

#include <stdint.h>
#include "mcp_driver.h"
#include <stdbool.h>

typedef struct can_message
{
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
	} can_message;

//initialize CAN bus
void can_init(void);

//send message to CAN bus
void can_message_send(can_message);

//returns true if a bus error occured
bool can_error(void);

//returns true if transmission finished
bool can_transmit_complete(void);

//receive message from CAN bus
can_message can_data_receive(void);

void can_int_vect(void);

#endif 