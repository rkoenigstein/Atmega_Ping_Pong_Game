#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

#include <avr/io.h>
#include <stdbool.h>

#define Kp 4
#define Ki 100
#define T 1 //integral time in [ms].

typedef struct
{
	int x;
	int y;
	int dir;
} JOY_POS;

typedef struct
{
	int l;
	int r;
} SLID;

enum JOY_DIR {NEUTRAL,LEFT, RIGHT, UP, DOWN, LEFT_UP, LEFT_DOWN, RIGHT_UP, RIGHT_DOWN};

void setMotorSpeed(JOY_POS joy_pos);

void enableMotor(void);

void disableMotor(void);

void setMotorDir(bool position);

double convertToAnalog(double startRange, double endRange, double val, double inRange);

uint8_t getEncoderValue (void);

void PIMotorController(void);


void PID_timer_init (void);

#endif /* MOTOR_CONTROL_H_ */