#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>


#define Kp 0.1
#define Ki 0.5
#define T 0.00102 //integral time in [ms].

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

void setMotorSpeed(void);

void enableMotor(void);

void disableMotor(void);

void setMotorDir(bool position);

double convertToAnalog(double startRange, double endRange, double val, double inRange);

void resetEncoder(void);

int getEncoderValue(void);

void PIMotorController(void);

void PID_timer_init (void);

void setMotorPosition(JOY_POS current_position);

void motor_init(void);

void shoot (void);

#endif /* MOTOR_CONTROL_H_ */