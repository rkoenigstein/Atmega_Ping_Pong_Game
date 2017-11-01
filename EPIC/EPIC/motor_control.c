#include "motor_control.h"
#include "TWI_Master.h"

uint8_t set_point=0;
uint8_t motor_speed=0;

void setMotorSpeed(JOY_POS joy_pos)
{
	bool position = false;
	double val = 0;
	double inRange = 127;
	switch(joy_pos.dir)
	{
		case UP:
		{
			position = false;
			val = joy_pos.y-125;
			break;
		}
		case DOWN:
		{
			position = true;
			val = 125 - joy_pos.y;
			break;
		}
		default:
		{
			return;
		}
	}
	
	enableMotor();
	
	
	setMotorDir(position);
	
	//provide analog voltage between 0V and 5V through DAC
	uint8_t analog = (uint8_t) convertToAnalog(0.0, 255.0, val, inRange);
	printf("analog: %d \n", analog);
	unsigned char msg[3] = {0x50, 0x0, analog};
	TWI_Start_Transceiver_With_Data(msg, 3);
}

void enableMotor(void)
{
	//enable motor
	DDRH = 0xFF;
	PORTH |= (1<<PH4);
}

void disableMotor(void)
{
	//disable motor
	PORTH &= ~(1<<PH4);
}

//position == false -> left
//position == true -> right
void setMotorDir(bool position)
{
	//set direction of motor
	DDRH = 0xFF;
	if(position)
	{
		PORTH |= (1<<PH4);
	}
	else
	{
		PORTH &= ~(1<<PH4);
	}
}

double convertToAnalog(double startRange, double endRange, double val, double inRange)
{	
	return (val/inRange)*(endRange-startRange)+startRange;
}

uint8_t getEncoderValue (void)
{
	DDRK=0x00;
	return PORTK;
}

void PIMotorController(void)
{
	static uint8_t esum=0;
	uint8_t encoder=getEncoderValue();
	uint8_t e=encoder-set_point;
	esum += e;
	
	motor_speed= Kp*e+Ki*T*esum;
}


/*void PID_timer_init (void)
{
	//set timer mode normal
	TCCR0A = 0x00;
	TCCR0B &= ~(1<<WGM02);
	
	//clock prescaler to 64  around 1 ms
	TCCR0B &= ~(1<<CS02);
	TCCR0B |= (1<<CS01) | (1<<CS00);

	
	//enable interrupt for counter overflow
	TIMSK0 |= (1<<TOIE0);
}

ISR(TIMER0_OVF_vect)
{
	printf ("interrupted by timer 0 for PI controller\n");
	PIMotorController();
}*/