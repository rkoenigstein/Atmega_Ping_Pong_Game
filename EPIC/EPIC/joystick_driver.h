#ifndef JOYS
#define JOYS

#define JOY_H 4
#define JOY_V 5
#define SL_L 7
#define SL_R 6// 7

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

/* calibrates the joystick and stores the maximum and minimum value */
void calibrateJoystick(void);

/* calibrates the sliders and stores min and max values */
void calibrateSlider(uint8_t which_slider);
void calibrateLeftSlider(void);
void calibrateRightSlider(void);

/* returns the slider positions from the USB multifunction board*/
SLID SLID_getPosition(void);

/* converts the joystick position from its enum value to a String */
static inline char *JOY_POS_toString(enum JOY_DIR joy_dir)
{
	static char *strings[] = { "NEUTRAL", "LEFT", "RIGHT", "UP", "DOWN", "LEFT_UP", "LEFT_DOWN", "RIGHT_UP", "RIGHT_DOWN"};

	return strings[joy_dir];
}

#endif
