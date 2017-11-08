#include <stdlib.h>
#include <inttypes.h>
#include "motor_control.h"
#include "TWI_Master.h"

#define F_CPU 16000000
#include <util/delay.h>

int16_t current_joy_pos;
int16_t old_joy_pos;

int global_current_direction = NEUTRAL;
bool global_current_position = false;
uint8_t global_motor_speed;

void motor_init(void)
{
	enableMotor();
	PID_timer_init ();
}

void PID_timer_init(void)
{
	//set timer mode normal
	TCCR0A &= ~(1 << WGM01) & ~(1 << WGM00);

	TCCR0B &= ~(1 << WGM02);

	//clock prescaler to 64  around 1 ms
	TCCR0B &= ~(1 << CS01);
	TCCR0B |= (1 << CS02) | (1 << CS00);

	//enable interrupt for counter overflow
	TIMSK0 |= (1 << TOIE0);
}

void setMotorSpeed(void)
{
	double inRange = 130;
	int val=0;

	switch(global_current_direction)
	{
		case NEUTRAL:
		{
			val = 0;
			break;
		}
		case UP:
		{
			global_current_position = false;
			val = global_motor_speed;
			break;
		}
		case DOWN:
		{
			global_current_position = true;
			val = global_motor_speed;
			break;
		}
		default:
		{
			return;
		}
	}

	//provide analog voltage between 0V and 5V through DAC
	global_motor_speed = (uint8_t) convertToAnalog(0.0, 255.0, val, inRange);

	//send digital motor speed to DAC
	unsigned char msg[3] = {0x50, 0x0, global_motor_speed};
	TWI_Start_Transceiver_With_Data(msg, 3);
}
void setMotorPosition(JOY_POS current_position)
{
	current_joy_pos = (current_position.y - 127);// << 8;
	global_current_direction = current_position.dir;
}

void enableMotor(void)
{
	//enable motor
	DDRH = 0xFF;
	PORTH |= (1 << PH4);
}

void disableMotor(void)
{
	//disable motor
	PORTH &= ~(1 << PH4);
	TIMSK0 &= ~(1 << TOIE0);
}

void setMotorDir(bool position)
{
	//set direction of motor
	DDRH = 0xFF;
	if(position)
	{
		PORTH |= (1 << PH1);
	}
	else
	{
		PORTH &= ~(1 << PH1);
	}
}

double convertToAnalog(double startRange, double endRange, double val, double inRange)
{
	return (val / inRange) * (endRange - startRange) + startRange;
}

int getEncoderValue(void)
{
	int encoder_val = 0;

	DDRK = 0x00;
	DDRH = 0xFF;

	//set !OE low to enable output of encoder
	PORTH &= ~(1 << PH5);

	//set SEL low to get high byte
	PORTH &= ~(1 << PH3);

	//wait about 20 us
	_delay_us(20);

	//read MSB
	encoder_val = PINK << 8;

	//wait about 20 us
	_delay_us(20);

	//read LSB
	encoder_val |= PINK;

	resetEncoder();

	//set !OE high to disable output of encoder
	PORTH |= (1<<PH5);

	return encoder_val;
}

void resetEncoder(void)
{
	//toggle !RST to reset encoder
	PORTH &= ~(1 << PH6);
	_delay_us(5);
	PORTH |= (1 << PH6);
}

void shoot_init(void)
{
	DDRL |= (1 << PL6);
}

void PIMotorController(void)
{
	global_motor_speed=0x60;
	setMotorDir(current_joy_pos > 0);
	
	/*static int esum = 0;
	int encoder = getEncoderValue();
	int16_t e = encoder - current_joy_pos;
	if(global_current_direction == NEUTRAL)
	{
		return;
	}
	
	if(old_joy_pos != current_joy_pos)
		esum += e;
	//printf("e: %d \n", e);
	int16_t new_val = (Kp * e + Ki * T * esum);
	//printf("new val: %d \n", (uint8_t) abs(new_val));
	global_motor_speed = (uint8_t) abs(new_val);
	setMotorDir(new_val > 0);*/

	//printf("analog: %d \n", global_motor_speed);
	if(global_current_direction != NEUTRAL)
	{
		unsigned char msg[3] = {0x50, 0x0, global_motor_speed};
		TWI_Start_Transceiver_With_Data(msg, 3);
		old_joy_pos = current_joy_pos;
	}
	else
	{
		unsigned char msg[3] = {0x50, 0x0, 0};
		TWI_Start_Transceiver_With_Data(msg, 3);
		old_joy_pos = current_joy_pos;
	}
	
}

void shoot(void)
{
	PORTL |= (1 << PL6);
	_delay_ms(50);
	PORTL &= ~(1 << PL6);
}

/* interrupt service routine for timer overflow to update motor control */
ISR(TIMER0_OVF_vect)
{
	PIMotorController();
}
