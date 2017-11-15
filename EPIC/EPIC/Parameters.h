#ifndef PARAMETERS_H_
#define PARAMETERS_H_

//#define ATMEGA2560

#define MAX_STRING_LENGTH 16

/* IDs for CAN messages */
enum CAN_IDS {JOY, SLIDERS, BUTTONS, CAN_SLEEP, PLAY_SONG, SCORE};

/* Right, left and direction for CAN message */
enum CAN_POS {R, L, DIR};

/* Songs */
#define HARRY_POTTER 0
#define TETRIS 1
#define CANTINA_BAND 2
#define POKEMON 3

#endif
