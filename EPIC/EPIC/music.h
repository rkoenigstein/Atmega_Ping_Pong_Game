#ifndef MUSIC_H_
#define MUSIC_H_

#include "music_notes.h"
#include "Parameters.h"

#ifdef ATMEGA2560
  #define F_CPU 16000000 //Clock speed
#else
  #define F_CPU 4915200 // Clock speed
#endif
#include <util/delay.h>

#define MUSIC_OUT_PORT DDRA
#define MUSIC_PORT PORTA
#define MUSIC_PIN PA1

/* initialize pin for buzzer output */
void music_init(void);

/* play a song */
void play_song(uint8_t songnumber);

#endif
