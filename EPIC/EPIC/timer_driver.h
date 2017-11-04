#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define TOP 131
#define BOTTOM 56
#define PERIOD 1250

/* initializing timer in mode 14 for pwm output with clk prescaler */
void timer_init(void);

#endif
