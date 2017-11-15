#ifndef SERVO_DRIVER_H_
#define SERVO_DRIVER_H_

#include <stdint.h>
#include <avr/io.h>
#include "timer_driver.h"

uint8_t calculateDutyCycle(uint8_t servo_pos);

#endif
