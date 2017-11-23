#include <stdio.h>
#include "joystick_driver.h"
#include "adc_driver.h"
#include "uart_driver.h"
#include "data_fit.h"
#include "oled_driver.h"

#ifdef ATMEGA2560
	#define F_CPU 16000000
#else
	#define F_CPU 4915200
#endif
#include <util/delay.h>

JOY_POS mid_point = { .x = 125, .y = 129 };

uint8_t margin = 15;

void USB_init()
{
	//set PIN 0 and 1 of port B as inputs for buttons
	DDRB &= ~(1 << PB0) & ~(1 << PB1);
}

bool JOY_button(int button)
{
	//printf("%x", ~(PINB & (1 << button)));
	return  (PINB & (1 << button));
}

JOY_POS JOY_getPosition(void)
{
	uint8_t x[15];
	uint8_t i = 0;
	JOY_POS real;

	for(i = 0; i < 15; i++)
	{
		x[i] = ADC_read(JOY_H);
		_delay_us(10);
	}
	real.x = data_fit(x, 15, 2, 2, 5);

	for(i = 0; i < 15; i++)
	{
		x[i] = ADC_read(JOY_V);
		_delay_us(10);
	}
	real.y = data_fit(x, 15, 2, 2, 5);

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
	uint8_t value[15];
	SLID slid;
	uint8_t i=0;
	for (i = 0; i < 15; i++)
	{
		value[i] = ADC_read(SL_L);
		_delay_us(10);
	}
	slid.l = data_fit(value, 15, 2, 2, 4);
	for (i = 0; i < 15; i++)
	{
		value[i] = ADC_read(SL_R);
		_delay_us(10);
	}
	slid.r = data_fit(value, 15, 2, 2, 4);
	//printf("left %d, right %d \n", value.l, value.r);
	return slid;
}

uint8_t Y_getDirection(JOY_POS in)
{
	return in.dir;
}

void TEST_USB_BOARD(void)
{
	/*JOY_POS value;
	SLID slid;
	while(1)
	{
		value = JOY_getPosition();
		printf("Joystick position x=%d , y=%d , direction=%s\n", value.x,  value.y,  JOY_POS_toString(value.dir));
		slid = SLID_getPosition();
		printf("Slider Position: left=%d , right=%d\n",  slid.l,  slid.r);
		_delay_ms(500);
	}*/
}
