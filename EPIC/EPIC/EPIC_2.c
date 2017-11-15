#include "Parameters.h"
#include "uart_driver.h"
#include "MCP2515.h"

#ifdef ATMEGA2560
	#define F_CPU 16000000 //Clock speed
#else
	#define F_CPU 4915200 // Clock speed
#endif
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "can_driver.h"
#include "timer_driver.h"
#include "ir_driver.h"
#include "motor_control.h"
#include "servo_driver.h"
#include "TWI_Master.h"
//#include "music.h"
#include <stdbool.h>
#include <avr/sleep.h>

can_message can_msg;
JOY_POS current_joy_pos;
SLID current_slider;
int cur_top = BOTTOM + (TOP-BOTTOM)/2;

int score = 0;

void sleep_init (void)
{
	//select Power-down mode
	SMCR |= (1 << SM1);
	SMCR &= ~(1 << SM0) & ~(1 << SM2);
}

void main_init (void)
{
	cli();
	shoot_init();
	uart_init();
	can_init();
	timer_init();
	ir_init();
	TWI_Master_Initialise();
	sei();
	motor_init();
	//sleep_init();
	//music_init();
	printf("INIT DONE\n");
}

void go_to_sleep (void)
{
	// set SE to one
	SMCR |= (1 << SE);

	//Check interrupts enable
	sei();

	//sleep
	sleep_cpu();

	//disable SE
	SMCR &= ~(1 << SE);
}

void update_OCR(uint8_t servo_pos)
{
	//DDRE |= (1 << PE3);
	OCR3A = (uint8_t) calculateDutyCycle(servo_pos);
}

void updateScore(void)
{
	int val=0;
	bool flag = false;
	for(uint8_t i=0; i<10;i++)
	{
		val = getIRValue();
		flag = val > 2 ? true : false;
	}
	if(!flag)
	{
		score++;
		while (getIRValue()< 3);
		_delay_ms(1000);
	}
}

int main(void)
 {

	main_init();

	/*while(1)
	{
		play_song(1);
	}*/
	
	
	while(1)
	{
		//printf("hey\n");
		//printf("IR value: %d\n", getIRValue());
		//updateScore();
		//printf("The score is %d\n", score);
		//printRegisters();
		_delay_ms(10);

		can_msg = can_data_receive();

		switch(can_msg.id)
		{
			case JOY:
			{
				printf("Got Joy pos \n");
				if(can_msg.length != 3)
				{
					printf("ERROR IN CAN MSG, WRONG LENGTH FOR JOY POS\n");
					break;
				}
				current_joy_pos.x = can_msg.data[R];
				current_joy_pos.y = can_msg.data[L];
				current_joy_pos.dir = can_msg.data[DIR];
				printf("JOY x: %d, JOY y: %d, JOY dir: %d\n", current_joy_pos.x, current_joy_pos.y, current_joy_pos.dir);
				setMotorPosition(current_joy_pos);
				break;
			}
			case BUTTONS:
			{
				uint8_t button = can_msg.data[0];
				printf("Got button: %d\n", button);
				if(can_msg.length != 1)
				{
					printf("ERROR IN CAN MSG, WRONG LENGTH FOR BUTTONS\n");
					break;
				}
				if (button == R)
				{
					shoot();
					printf("Right button SHOOT\n");
				}
				if (button == L)
					printf("Left button Press the other button\n");
				break;
			}
			case SLIDERS:
			{
				printf("Got sliders\n");
				if(can_msg.length != 2)
				{
					printf("ERROR IN CAN MSG, WRONG LENGTH FOR SLIDERS\n");
					break;
				}
				current_slider.r = can_msg.data[R];
				current_slider.l = can_msg.data[L];
				//printf("right slider: %d, left slider: %d\n", current_slider.r, current_slider.l);
				update_OCR(current_slider.r);
				break;
			}
			case CAN_SLEEP:
			{
				printf("Go to sleep, send me a CAN message so that I will wake up\n");
				go_to_sleep();
				printf("Woke up\n");
				break;
			}
			case PLAY_SONG:
			{
				printf("Playing music\n");
				//play_song(can_msg.data[0]);
				break;
			}
			default:
			{
				printf("CAN ID unknown\n");
				break;
			}
		}

    }

	//TEST_music();
	//test_shoot();
}


void test_shoot(void)
{
	int i=0;
	while(1)
	{
		shoot();
		printf("Attempt %d\n", i);
		i++;
		_delay_ms(2000);
	}
}
