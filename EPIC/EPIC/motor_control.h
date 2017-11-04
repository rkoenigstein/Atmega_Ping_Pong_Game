#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>

#define Kp 0.1
#define Ki 0.5
#define T 0.00102 //integral time in [ms] -> counter overflow

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

/* enables motor and initializes timer for motor control */
void motor_init(void);

/* initializes timer for updating motor control */
void PID_timer_init (void);

/* enables the motor */
void enableMotor(void);

/* disables the motor */
void disableMotor(void);

/* sets the motor speed*/
void setMotorSpeed(void);

/* sets the direction of the motor */
void setMotorDir(bool position);

/* converts a value from range inRange to the range specified by startRange and endRange */
double convertToAnalog(double startRange, double endRange, double val, double inRange);

/* reset the motor encoder to restart counting the distance */
void resetEncoder(void);

/* returns the 16bit motor encoder value*/
int getEncoderValue(void);

/* update the PI motor control */
void PIMotorController(void);

/* updates the current joystick position */
void setMotorPosition(JOY_POS current_position);

/* shoots a 50ms kick with the solenoid */
void shoot(void);

#endif
