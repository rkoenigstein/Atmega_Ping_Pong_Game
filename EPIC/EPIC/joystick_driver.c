//Joystick driver
#include "joystick_driver.h"
#include "adc.h"
#include "uart_driver.h"
#include <util/delay.h>

//
void JOY_init()
{
	//set PIN 0 and 1 of port B as inputs
	DDRB &= (0<<0)&(0<<1);	
}

void JOY_calibrate()
{
	
}

bool JOY_button(int button)
{
	return PORTB&(1<<button);
}

JOY_POS JOY_getPosition(void)
{
	JOY_POS value;
	value.x=ADC_read(JOY_H);
	value.y=ADC_read(JOY_V);
	
	if(value.y >= -value.x+255 && value.y>=value.x)
	{
		value.dir = UP;
	}
	if(value.y >= -value.x+255 && value.y<value.x)
	{
		value.dir = RIGHT;
	}			
	if(value.y < -value.x+255 && value.y>=value.x)
	{
		value.dir = LEFT;
	}
	if(value.y < -value.x+255 && value.y<value.x)
	{
		value.dir = DOWN;
	}
	return value;
}

SLID SLID_getPosition(void)
{
	SLID value;
	value.l=ADC_read(SL_L);
	value.r=ADC_read(SL_R);
	return value;
}

//DO we really need to get the direction ??
int Y_getDirection(JOY_POS in)
{
	return in.dir;
}


//TEST function

void TEST_USB_BOARD(void)
{
	JOY_POS value;
	SLID slid;
	while(1)
	{
		value=JOY_getPosition();
		printf("Joystick position x=%d , y=%d , direction=%s\n", value.x,  value.y,  JOY_POS_toString(value.dir));
		slid=SLID_getPosition();
		printf("Slider Position: left=%d , right=%d\n",  slid.l,  slid.r);
		_delay_ms(500);
	}
}