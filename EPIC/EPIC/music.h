#ifndef MUSIC_H_
#define MUSIC_H_

#include "Parameters.h"
#include <avr/io.h>
#include <stdbool.h>

#ifdef ATMEGA2560
  #define F_CPU 16000000 //Clock speed
#else
  #define F_CPU 4915200 // Clock speed
#endif
#include <util/delay.h>

#define PRESCALER 8

#define MUSIC_OUT_PORT DDRL
#define MUSIC_PORT PORTL
#define MUSIC_PIN DDL3

#define DEFAULT_WHOLE_NOTE_DURATION 4000.0

/* initialize pin for buzzer output */
void music_init(void);

/* play a song */
void play_song(void);

/* play available songs for testing purposes */
void TEST_music(void);

/* start or end playing a song */
void setPlaying(bool play, int song);

/* function to introduce variable delay */
void variable_delay_in_ms(uint16_t counter);

/* initialize song */
void init_song(void);

#endif
