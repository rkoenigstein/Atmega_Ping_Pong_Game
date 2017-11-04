#ifndef IR_DRIVER_H_
#define IR_DRIVER_H_

#include <avr/io.h>

/* enable ADC, select ADC channel, reference VCC and set prescaler */
void ir_init(void);

/* returns IR sensor value */
int getIRValue(void);

/* select ADC channel of IR conversion */
void selectADCChannel(void);

#endif
