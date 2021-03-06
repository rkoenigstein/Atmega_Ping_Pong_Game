#ifndef JOYS
#define JOYS

//MUX values for ADC
#define JOY_H 4 //Ch1, PIN3, JOY_x
#define JOY_V 5 //Ch2, PIN4, JOY_y
#define SL_R 6 //Ch3, PIN6, SLID_L
#define SL_L 7 //Ch4, PIN5, SLID_R

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
	uint8_t x;
	uint8_t y;
	uint8_t dir;
} JOY_POS;

typedef struct
{
	uint8_t l;
	uint8_t r;
} SLID;

enum JOY_DIR {NEUTRAL,LEFT, RIGHT, UP, DOWN, LEFT_UP, LEFT_DOWN, RIGHT_UP, RIGHT_DOWN};

/* initializes the I/O pins of the MCU where the joystick is connected */
void USB_init(void);

/* returns whether the joystick button is pressed or not */
bool JOY_button(int button);

/* returns the position of the joystick */
JOY_POS JOY_getPosition(void);

/* returns the direction of the joystick */
int JOY_getDirection(JOY_POS in);

/* returns the slider positions from the USB multifunction board*/
SLID SLID_getPosition(void);

/* converts the joystick position from its enum value to a String */
static inline char *JOY_POS_toString(enum JOY_DIR joy_dir)
{
	static char *strings[] = { "NEUTRAL", "LEFT", "RIGHT", "UP", "DOWN", "LEFT_UP", "LEFT_DOWN", "RIGHT_UP", "RIGHT_DOWN"};

	return strings[joy_dir];
}

#endif
