//Joystick driver
#include "joystick_driver.h"
#include "adc.h"
#include "uart_driver.h"
#include <stdio.h>
#include <util/delay.h>

JOY_POS mid_point = { .x = 125, .y = 129};
uint8_t margin = 15;

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
	int val_x = 0;
	int val_y = 0;
	int sum_x = 0;
	int sum_y = 0;
	int largest_x = 0;
	int largest_y = 0;
	int smallest_x = 255;
	int smallest_y = 255;
	for(int i=0;i<7;i++)
	{
		val_x = ADC_read(JOY_H);
		val_y = ADC_read(JOY_V);
		smallest_x = val_x < smallest_x ? val_x : smallest_x;
		smallest_y = val_y < smallest_y ? val_y : smallest_y;
		largest_y = val_y > largest_y ? val_y : largest_y;
		largest_x = val_x > largest_x ? val_x : largest_x;
		sum_x += val_x;
		sum_y += val_y;
	}
	sum_x = sum_x - largest_x - smallest_x;
	sum_y = sum_y - largest_y - smallest_y;	 
	sum_x /= 5;
	sum_y /= 5;
	value.x = sum_x;
	value.y = sum_y;
	
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
	
	switch(value.dir)
	{
		case UP:
		{
			value.dir = value.y > mid_point.y + margin ? value.dir : NEUTRAL; 
			break;
		}
		case RIGHT:
		{
			value.dir = value.x > mid_point.x + margin ? value.dir : NEUTRAL; 
			break;
		}
		case DOWN:
		{
			value.dir = value.y < mid_point.y - margin ? value.dir : NEUTRAL; 
			break;
		}
		case LEFT:
		{
			value.dir = value.x < mid_point.x - margin ? value.dir : NEUTRAL; 
			break;
		}
		default:
		{
			printf("Error receiving joystick value\n");
			break;
		}
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