#ifndef GAME_1_H_
#define GAME_1_H_

#include <stdint.h>
#include <stdbool.h>
#include "joystick_driver.h"
#include "graphic.h"
#include "oled_driver.h"
#include "Parameters.h"
#include "song_handler.h"

//screen parameters
#define M 				8
#define N 				128

//playing space parameters
#define LIM_UP 			11
#define LIM_DOWN 		63
#define LIM_RIGHT 		127
#define LIM_LEFT 		0

//player parameters
#define DIM_PLAYER 		20
#define Y_PLAYER		LIM_DOWN-2	

//little blocks grid parameters
#define L_X 			12
#define L_Y				3
#define	EMPTY_SPACE_X	2
#define EMPTY_SPACE_Y	2
#define N_X				(int)126/(EMPTY_SPACE_X+L_X)
#define N_Y				3

//starting ball position
#define B_X				0
#define B_Y				30

enum{UP_RIGHT, UP_LEFT, DOWN_RIGHT, DOWN_LEFT}; //for ball which moves 45°

//define a ball
struct ball
{
	POS pos;
	uint8_t dir;
};
typedef struct ball BALL;

//define a player (bar)
struct player
{
	RECT rect;
	uint8_t dir;
};
typedef struct player PLAYER;

/* play ping pang or bar game */
void ping_pong_idle(void);

#endif