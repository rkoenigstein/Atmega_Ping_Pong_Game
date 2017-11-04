#include <stdio.h>
#include <util/delay.h>
#include "joystick_driver.h"
#include "adc_driver.h"
#include "uart_driver.h"

JOY_POS mid_point = { .x = 125, .y = 129};
uint8_t margin = 15;

void JOY_init()
{
	//set PIN 0 and 1 of port B as inputs
	DDRB &= (0 << PB0) & (0 << PB1);
}

bool JOY_button(int button)
{
	return PORTB & (1 << button);
}

JOY_POS JOY_getPosition(void)
{
	int x[16];
	int y[16];
	JOY_POS real;
	for(int i = 0; i < 15; i++)
	{
		x[i] = ADC_read(JOY_H);
		y[i] = ADC_read(JOY_V);
	}

	real.x = data_fit(x, 15, 2, 10, 3);
	real.y = data_fit(y, 15, 2, 10, 3);
	if(real.y >= -real.x + 255 && real.y >= real.x)
	{
		real.dir = UP;
	}
	if(real.y >= -real.x + 255 && real.y < real.x)
	{
		real.dir = RIGHT;
	}
	if(real.y < -real.x + 255 && real.y >= real.x)
	{
		real.dir = LEFT;
	}
	if(real.y < -real.x + 255 && real.y < real.x)
	{
		real.dir = DOWN;
	}

	switch(real.dir)
	{
		case UP:
		{
			real.dir = real.y > mid_point.y + margin ? real.dir : NEUTRAL;
			break;
		}
		case RIGHT:
		{
			real.dir = real.x > mid_point.x + margin ? real.dir : NEUTRAL;
			break;
		}
		case DOWN:
		{
			real.dir = real.y < mid_point.y - margin ? real.dir : NEUTRAL;
			break;
		}
		case LEFT:
		{
			real.dir = real.x < mid_point.x - margin ? real.dir : NEUTRAL;
			break;
		}
		default:
		{
			printf("Error receiving joystick value\n");
			break;
		}
	}

	return real;
}

SLID SLID_getPosition(void)
{
	SLID value;
	value.l = ADC_read(SL_L);
	value.r = ADC_read(SL_R);
	return value;
}

int Y_getDirection(JOY_POS in)
{
	return in.dir;
}

void TEST_USB_BOARD(void)
{
	JOY_POS value;
	SLID slid;
	while(1)
	{
		value = JOY_getPosition();
		printf("Joystick position x=%d , y=%d , direction=%s\n", value.x,  value.y,  JOY_POS_toString(value.dir));
		slid = SLID_getPosition();
		printf("Slider Position: left=%d , right=%d\n",  slid.l,  slid.r);
		_delay_ms(500);
	}
}
