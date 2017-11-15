#ifndef MUSIC_H_
#define MUSIC_H_

#include "Parameters.h"
#include <avr/io.h>

#include "Parameters.h"
#ifdef ATMEGA2560
  #define F_CPU 16000000 //Clock speed
#else
  #define F_CPU 4915200 // Clock speed
#endif
#include <util/delay.h>

#define MUSIC_OUT_PORT DDRL
#define MUSIC_PORT PORTL
#define MUSIC_PIN DDL3

/* initialize pin for buzzer output */
void music_init(void);

/* play a song */
void play_song(uint8_t songnumber);

/* play available songs for testing purposes */
void TEST_music(void);

#endif
