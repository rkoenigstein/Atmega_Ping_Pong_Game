//Joystick driver
// BETTER NAME USB DRIVER =)
#ifndef JOYS
#define JOYS 

#include "adc.h"
#include "uart_driver.h"
#include <stdbool.h>
#include <util/delay.h>

#define JOY_H 4
#define JOY_V 5
#define SL_L 6
#define SL_R 7


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

//
void JOY_init(void);

//
void JOY_calibrate(void);

bool JOY_button(int button);

//
JOY_POS JOY_getPosition(void);

//
int JOY_getDirection(JOY_POS in);

//
SLID SLID_getPosition(void);

static inline char *JOY_POS_toString(enum JOY_DIR joy_dir)
{
	static const char *strings[] = { "NEUTRAL", "LEFT", "RIGHT", "UP", "DOWN", "LEFT_UP", "LEFT_DOWN", "RIGHT_UP", "RIGHT_DOWN"};

	return strings[joy_dir];
}

#endif