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

JOY_POS joy_max_point = { .x = 255, .y = 255 };

JOY_POS joy_min_point = { .x = 0, .y = 0 };

SLID left_slider_calib = { .l = 0, .r = 255 };
SLID right_slider_calib = { .l = 0, .r = 255 };

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

void calibrateLeftSlider(void)
{
	calibrateSlider(SL_L);
}

void calibrateRightSlider(void)
{
	calibrateSlider(SL_R);
}

void calibrateSlider(uint8_t which_slider)
{
	/*bool high = true;
	bool slider_done = false;
	while(!slider_done)
	{
		position pos = { .page = 0, .column = 1 };
		if(which_slider == SL_L)
		{
			print_string_to_buffer("Put left slider", pos);
		}
		else
		{
			print_string_to_buffer("Put right slider", pos);
		}
		pos.page++;
		if(high)
		{
			print_string_to_buffer("to right and", pos);
		}
		else
		{
			print_string_to_buffer("to left and", pos);
		}
		pos.page++;
		print_string_to_buffer("press the left", pos);
		pos.page++;
		print_string_to_buffer("button when", pos);
		pos.page++;
		print_string_to_buffer("done.", pos);
		print_buffer();

		while(!JOY_button(0));
		if(high && which_slider == SL_L ? SLID_getPosition().l : SLID_getPosition().r < 240 || !high && which_slider == SL_L ? SLID_getPosition().l : SLID_getPosition().r > 15)
		{
			pos.page = 0;
			print_string_to_buffer("Slider must", pos);
			pos.page = 1;
			if(high)
			{
				print_string_to_buffer("be to right!", pos);
			}
			else
			{
				print_string_to_buffer("be to left!", pos);
			}
			print_buffer();
		}
		else
		{
			slider_done = high ? false : true;
			if(!high)
			{
				pos.page = 0;
				pos.column = 1;
				print_string_to_buffer("Done with", pos);
				pos.page++;
				print_string_to_buffer("slider calib-", pos);
				pos.page++;
				print_string_to_buffer("ation!", pos);
				print_buffer();
				if(which_slider == SL_L)
				{
					left_slider_calib.r = SLID_getPosition().l;
				}
				else
				{
					right_slider_calib.r = SLID_getPosition().r;
				}
				_delay_ms(1000);
			}
			else
			{
				if(which_slider == SL_L)
				{
					left_slider_calib.l = SLID_getPosition().l;
				}
				else
				{
					right_slider_calib.l = SLID_getPosition().r;
				}
			}
			high  = !high;
		}
	}
	_delay_ms(500);
	print_thumb();
	_delay_ms(1000);*/
}

void calibrateJoystick(void)
{
	/*bool y_done = false, x_done = false;
	bool top = true;

	//calibrate joystick vertically
	while(!y_done)
	{
		position pos = { .page = 0, .column = 1 };
		clear_buffer();
		print_string_to_buffer("Push joystick  ", pos);
		pos.page++;
		if(top)
		{
			print_string_to_buffer("to top and", pos);
		}
		else
		{
			print_string_to_buffer("to bottom and", pos);
		}
		pos.page++;
		print_string_to_buffer("press the right", pos);
		pos.page++;
		print_string_to_buffer("button when", pos);
		pos.page++;
		print_string_to_buffer("done.", pos);
		print_buffer();

		while(!JOY_button(0));
		if(top && JOY_getPosition().y < 240 || !top && JOY_getPosition().y > 15)
		{
			pos.page = 0;
			clear_buffer();
			print_string_to_buffer("Joystick must", pos);
			pos.page = 1;
			if(top)
			{
				print_string_to_buffer("be at top!", pos);
			}
			else
			{
				print_string_to_buffer("be at bottom!", pos);
			}
			print_buffer();
			_delay_ms(1500);
		}
		else
		{
			y_done = top ? false : true;
			if(!top)
			{
				pos.page = 0;
				pos.column = 1;
				print_string_to_buffer("Done with ver-", pos);
				pos.page++;
				print_string_to_buffer("tical calib-", pos);
				pos.page++;
				print_string_to_buffer("ation", pos);
				print_buffer();
				joy_min_point.y = JOY_getPosition().y;
				_delay_ms(1000);
			}
			else
			{
				joy_max_point.y = JOY_getPosition().y;
			}
			top  = !top;
		}
	}

	position pos = { .page = 0, .column = 1 };
	//same for horizontal direction
	while(!x_done)
	{
		pos.page = 0;
		pos.column = 1;
		clear_buffer();
		print_string_to_buffer("Push joystick ", pos);
		pos.page++;
		if(top)
		{
			print_string_to_buffer("to right and", pos);
		}
		else
		{
			print_string_to_buffer("to left and", pos);
		}
		pos.page++;
		print_string_to_buffer("press the right", pos);
		pos.page++;
		print_string_to_buffer("button when", pos);
		pos.page++;
		print_string_to_buffer("done.", pos);
		print_buffer();

		while(!JOY_button(0));
		if(top && JOY_getPosition().x < 240 || !top && JOY_getPosition().x > 15)
		{
			pos.page = 0;
			clear_buffer();
			print_string_to_buffer("Joystick must", pos);
			pos.page = 1;
			if(top)
			{
				print_string_to_buffer("be at right!", pos);
			}
			else
			{
				print_string_to_buffer("be at left!", pos);
			}
			print_buffer();
			_delay_ms(1500);
		}
		else
		{
			x_done = top ? false : true;
			if(!top)
			{
				pos.page = 0;
				pos.column = 1;
				print_string_to_buffer("Done with hor-", pos);
				pos.page++;
				print_string_to_buffer("izontal calib-", pos);
				pos.page++;
				print_string_to_buffer("ation", pos);
				print_buffer();
				joy_min_point.x = JOY_getPosition().x;
				_delay_ms(500);
			}
			else
			{
				joy_max_point.x = JOY_getPosition().x;
			}
			top  = !top;
		}
	}

	while(!JOY_button(0) && !(115 < JOY_getPosition().x < 140) && !(115 < JOY_getPosition().y < 140))
	{
		pos.page = 0;
		pos.column = 1;
		clear_buffer();
		print_string_to_buffer("Leave Joystick", pos);
		pos.page++;
		print_string_to_buffer("in the middle", pos);
		pos.page++;
		print_string_to_buffer("and press left", pos);
		pos.page++;
		print_string_to_buffer("button!", pos);
		print_buffer();
	}
	mid_point = JOY_getPosition();
	pos.page = 0;
	pos.column = 1;
	print_string_to_buffer("Done with", pos);
	pos.page++;
	print_string_to_buffer("calibration!", pos);
	print_buffer();
	_delay_ms(1500);
	print_thumb();
	_delay_ms(2000);*/
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
