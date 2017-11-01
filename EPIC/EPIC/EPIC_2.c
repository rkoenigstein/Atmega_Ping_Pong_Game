#include "uart_driver_2560.h"
#include "MCP2515.h"

#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

//#include <avr/delay.h>

#include "can_driver_2560.h"
#include "timer_driver.h"
#include "ir_driver.h"
#include "motor_control.h"
#include "TWI_Master.h"
#include <stdbool.h>

can_message can_msg;
JOY_POS current_joy_pos;
int cur_top = BOTTOM + (TOP-BOTTOM)/2;

int score = 0;

enum CAN_IDS {JOY};

void main_init (void)
{
	uart_init(BAUDRATE);
	can_init();
	timer_init();
	ir_init();
	TWI_Master_Initialise();
	
	sei();
	printf("INIT DONE\n");
}

void update_OCR(uint8_t joy_x_pos)
{
	OCR4A = (uint8_t) calculateDutyCycle(joy_x_pos);	
}

void updateScore(void)
{
	/*int val=0;
	int flag=0;
	for(uint8_t i=0; i<10;i++)
	{
		val = getIRValue();
		if(val < 3)
		{
			flag++;
			if(flag>9)
			{
				score++;
				while (getIRValue()<3);
				i=11;
				break;
				
			}
		}
	}*/
	
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
		_delay_ms(2000);
	}
}

int main(void)
 {
	main_init();
    while(1)
    {
		//printf("hey\n");
		//printf("IR value: %d\n", getIRValue());
		updateScore();
		printf("The score is %d\n", score);
		_delay_ms(100);

		can_msg = can_data_receive();
		
		switch(can_msg.id)
		{
			case JOY: 
			{
				current_joy_pos.x = can_msg.data[0];
				current_joy_pos.y = can_msg.data[1];
				current_joy_pos.dir = can_msg.data[2];
				update_OCR(current_joy_pos.x);
				printf("JOY x: %d, JOY y: %d, JOY dir: %d\n", current_joy_pos.x, current_joy_pos.y, current_joy_pos.dir);
				setMotorSpeed(current_joy_pos);
				break;
			}
			default:
			{
				printf("CAN ID unknown\n");
				break;
			}
		}
		
    }
}