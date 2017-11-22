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
#include "music.h"
#include <stdbool.h>
#include <avr/sleep.h>

can_message can_msg;
JOY_POS current_joy_pos, old_joy_pos;
uint8_t current_right_slid, old_right_slid;
bool right_button = false;
bool play_music = false;
bool in_game = false;

int cur_top = BOTTOM + (TOP-BOTTOM)/2;

int score = 0;

bool with_ir = false;

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
	music_init();
	printf("INIT DONE\n");
}


void updateScore(void)
{
	int val = 0;
	for(uint8_t i = 0; i < 10; i++)
	{
		val += getIRValue();
	}
	val /= 10;
	printf("IR value=%d\n", val);

	
	if(val < 8)
	{
		score++;
		can_message can_msg = { .id = SCORE, .length = 1, .data[0] = score };
		can_message_send(can_msg);
		printf("CAN send score IR value=%d\n", val);
		_delay_ms(2000);
	}
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
	OCR3A = (uint8_t) calculateDutyCycle(servo_pos);
}

int main(void)
 {

	main_init();
	
	while(1)
	{
		_delay_ms(15);

		//update playing song if new CAN SONG message arrived
		if(play_music)
			play_song();
			
		_delay_ms(15);
		
		//update servo if new CAN SLID message arrived
		if(current_right_slid != old_right_slid)
		{
			old_right_slid = current_right_slid;
			update_OCR(current_right_slid);
		}
		
		_delay_ms(15);
		
		//update shoot if new CAN BUTTON message arrived
		if(right_button)
		{
			shoot();
			right_button = false;
		}
		
		_delay_ms(15);
		
		//update joystick position if new CAN JOY message arrived
		if(current_joy_pos.dir != old_joy_pos.dir || old_joy_pos.x != current_joy_pos.x || old_joy_pos.y != current_joy_pos.y)
		{
			//printf("old joy x: %d, y: %d, dir: %d, current x: %d, y: %d, dir: %d \n", old_joy_pos.x, old_joy_pos.y, old_joy_pos.dir, current_joy_pos.x, current_joy_pos.y, current_joy_pos.dir);
			old_joy_pos = current_joy_pos;
			setMotorPosition(current_joy_pos);
		}
		
		_delay_ms(15);
		
		//update score by means of checking IR value
		if(in_game && with_ir)
			updateScore();
    }
}

//interrupt service routine clearing the receive buffer interrupt bit to receive next message
ISR(INT3_vect)
{
	can_message can_msg;

	//read upper 8 bit of id
	can_msg.id = mcp_read(MCP_RXB0SIDH) << 3;
	
	//read lower 8 bit of id
	can_msg.id |= mcp_read(MCP_RXB0SIDL) >> 5;
	
	//read length of CAN data
	can_msg.length = mcp_read(MCP_RXB0DLC);
	
	//read CAN data
	for(uint8_t i = 0; i < can_msg.length; i++)
	can_msg.data[i] = mcp_read(MCP_RXB0D0+i);
	
	switch(can_msg.id)
	{
		case START_PING_PONG:
		{
			printf("START PING PONG \n");
			//play = true;
			//setPlaying(true, TETRIS);
			in_game = true;
			score = 0;
			motor_timer_on();
			break;
		}
		case STOP_PING_PONG:
		{
			printf("STOP PING PONG \n");
			//setPlaying(false, 0);
			//play = false;
			in_game = true;
			motor_timer_off();
			break;
		}
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
			//printf("JOY x: %d, JOY y: %d, JOY dir: %d\n", current_joy_pos.x, current_joy_pos.y, current_joy_pos.dir);
			break;
		}
		case BUTTONS:
		{
			right_button = R == can_msg.data[0];
			printf("Got button\n");
			if(can_msg.length != 1)
			{
				printf("ERROR IN CAN MSG, WRONG LENGTH FOR BUTTONS\n");
				break;
			}
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
			current_right_slid = can_msg.data[R];
			//printf("right slider: %d, left slider: %d\n", current_slider.r, current_slider.l);
			break;
		}
		case WITH_IR:
		{
			printf("WITH IR CAN RECEIVED\n");
			with_ir = true;	
			break;		
		}
		case WITHOUT_IR:
		{
			printf("WITHOUT IR CAN RECEIVED\n");
			with_ir = false;
			break;
		}
		case START_SONG:
		{
			play_music = true;
			printf("Playing music\n");
			setPlaying(true, can_msg.data[0]);
			break;
		}
		case END_SONG:
		{
			setPlaying(false, 0);
			printf("Stopping music\n");
			play_music = false;
			break;
		}
		default:
		{
			printf("CAN ID unknown\n");
			break;
		}
	}
	
	//allow new message to be received into the buffer
	mcp_write(MCP_CANINTF, MCP_RX0IF & 0x00);
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
