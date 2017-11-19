#ifndef PARAMETERS_H_
#define PARAMETERS_H_

//#define ATMEGA2560

#define MAX_STRING_LENGTH 16

/* IDs for CAN messages */
enum CAN_IDS {JOY, SLIDERS, BUTTONS, START_SONG, END_SONG, SCORE, STOP_PING_PONG, START_PING_PONG, RESET_SCORE, WITH_IR, WITHOUT_IR };

/* Right, left and direction for CAN message */
enum CAN_POS {R, L, DIR};

/* Songs */
#define HARRY_POTTER 0
#define TETRIS 1
#define CANTINA_BAND 2
#define POKEMON 3
#define IMPERIAL 4
#define MERRY_X_MAS 5
#define JINGLE_BELLS 6
#define LAST_CHRISTMAS 7

//sleep modes
#define POWER_DOWN 1
#define POWER_SAVE 0

#endif
