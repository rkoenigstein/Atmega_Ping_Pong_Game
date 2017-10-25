#include "servo_driver.h"
#include "uart_driver_2560.h"

uint8_t calculateDutyCycle(uint8_t joy_x_pos)
{
	//if joystick calibration implemented -> read joy max value
	uint8_t duty_cycle = TOP-(joy_x_pos/255.0)*(TOP-BOTTOM);
	
	//uint_8 is our great safety measure, as no value larger than 255 can be passed to the timer and 
	//hence if a larger value is passed, just an overflow to 0 will happen :)
	if(duty_cycle > TOP || duty_cycle < BOTTOM)
	{
		printf("SERVO VALUE OUT OF RANGE -> SET TO CENTER\n");
		duty_cycle = BOTTOM+(TOP-BOTTOM)/2;
	}
	return duty_cycle;
}