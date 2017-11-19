#ifndef SONG_HANDLER_H_
#define SONG_HANDLER_H_

#include "Parameters.h"
#include "joystick_driver.h"
#include "can_driver.h"
#include "oled_driver.h"

/* send CAN messag including the song selection */
void send_song_CAN(uint8_t song);

/* play selected song and display it */
void song_harry_potter(void);
void song_cantina_band(void);
void song_pokemon(void);
void song_tetris(void);
void song_octaves(void);
void song_jingle_bells(void);
void song_last_christmas(void);
void song_merry_x_mas(void);

/* stops music */
void send_stop_CAN(void);

/* display current song selection on display */
void displaySong(uint8_t song);

/* handle user input while song is played */
void handleUserInput(uint8_t song);

#endif