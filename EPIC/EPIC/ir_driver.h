#ifndef IR_DRIVER_H_
#define IR_DRIVER_H_

#include <avr/io.h>

void ir_init(void);

int getIRValue(void);

void selectADCChannel(void);

#endif /* IR_DRIVER_H_ */