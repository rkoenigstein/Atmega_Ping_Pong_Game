#ifndef JOYS
#define JOYS

#define JOY_H 4
#define JOY_V 5
#define SL_L 6
#define SL_R 7

#include <stdbool.h>
#include <stdint.h>

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

/* initializes the I/O pins of the MCU where the joystick is connected */
void JOY_init(void);

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
