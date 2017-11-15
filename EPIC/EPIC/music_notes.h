#ifndef MUSIC_NOTES_H_
#define MUSIC_NOTES_H_

#include <avr/pgmspace.h>
//#include <stdint.h>

#define pause 0.00

#define C 0
#define Cs 1
#define D 2
#define Ds 3
#define E 4
#define F 5
#define Fs 6
#define G 7
#define Gs 8
#define A 9
#define As 10
#define B 11

#define whole 1.0
#define half 0.5
#define quarter 0.25
#define octal 0.125
#define sixteenth 0.0625

#define NUM_OF_SONGS 4
/*
const float PROGMEM pause = 0.00;

const uint8_t PROGMEM C = 0;
const uint8_t PROGMEM Cs = 1;
const uint8_t PROGMEM D = 2;
const uint8_t PROGMEM Ds = 3;
const uint8_t PROGMEM E = 4;
const uint8_t PROGMEM F = 5;
const uint8_t PROGMEM Fs = 6;
const uint8_t PROGMEM G = 7;
const uint8_t PROGMEM Gs = 8;
const uint8_t PROGMEM A = 9;
const uint8_t PROGMEM As = 10;
const uint8_t PROGMEM B = 11;

const float PROGMEM whole = 1.0;
const float PROGMEM half = 0.5;
const float PROGMEM quarter = 0.25;
const float PROGMEM octal = 0.125;
const float PROGMEM sixteenth = 0.0625;

const uint8_t PROGMEM NUM_OF_SONGS = 4;
*/
#define point_note(x) ((x) * 1.5)
#define connected_note(x, y) ((x) + (y))

//music frequencies of notes according to http://www.phy.mtu.edu/~suits/notefreqs.html
//octaves 0 to 8, C, Cs, D, Ds, E, F, Fs, G, Gs, A, As, B
const float PROGMEM notes[9][12] =
{
  {16.35, 17.32, 18.35, 19.45, 20.60, 21.83, 23.12, 24.50, 25.96, 27.50, 29.14, 30.87}, //0
  {32.70, 34.65, 36.71, 38.89, 41.20, 43.65, 46.25, 49.00, 51.91, 55.00, 58.27, 61.74}, //1
  {65.41, 69.30, 73.42, 77.78, 82.41, 78.31, 92.50, 98.00, 103.83, 110.00, 116.54, 123.47}, //2
  {130.81, 138.59, 146.83, 155.56, 164.81, 174.61, 185.00, 196.00, 207.65, 220.00, 233.08, 246.94}, //3
  {261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392.00, 415.30, 440.00, 466.16, 493.88}, //4
  {523.25, 554.37, 587.33, 622.25, 659.25, 698.46, 739.99, 783.99, 830.61, 880.00, 932.33, 987.77}, //5
  {1046.50, 1108.73, 1174.66, 1244.51, 1318.51, 1396.91, 1479.98, 1567.98, 1661.22, 1760.00, 1864.66, 1975.53}, //6
  {2093.00, 2217.46, 2349.32, 2489.02, 2637.02, 2793.83, 2959.96, 3135.96, 3322.44, 3520.00, 3729.31, 3951.07}, //7
  {4186.01, 4434.92, 4698.63, 4978.03, 5274.04, 5587.65, 5919.91, 6271.93, 6644.88, 7040.00, 7458.62, 7902.13}, //8
};

//songs available to be played
const float PROGMEM songs_durations[NUM_OF_SONGS][61] =
{
  {
    quarter, point_note(quarter), octal, quarter, half, quarter, point_note(half), point_note(half),
    point_note(quarter), octal, quarter, half, quarter, connected_note(point_note(half), half),
    quarter, point_note(quarter), octal, quarter, half, quarter, half, quarter, half, quarter, point_note(quarter),
    octal, quarter, half, quarter, connected_note(point_note(half), half), quarter, half, quarter, half, quarter, half, quarter, half,
    quarter, point_note(quarter), octal, quarter, half, quarter, connected_note(point_note(half), half), quarter,
    half, quarter, half, quarter, half, quarter, half, quarter, point_note(quarter), octal, quarter, half, quarter, connected_note(point_note(half), half), quarter
  }, //harry potter - hedwig
  {
    quarter, octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, octal, octal, point_note(quarter), octal, quarter, quarter, quarter, quarter,
    octal, octal, octal, point_note(quarter), octal, quarter, octal, octal, point_note(quarter), octal, quarter, octal, octal, quarter, octal, octal, quarter,
    quarter, quarter, quarter, quarter, quarter, half, half, half, half, half, half, half, quarter, quarter, half, half, half, half, quarter, quarter, half, half,
    quarter, octal, octal
  }, //Tetris
  {
    quarter, quarter, quarter, quarter, octal, quarter, octal, octal, octal, quarter, octal, octal, octal, octal, octal, octal, octal, octal, point_note(quarter), connected_note(octal, half),
    quarter, quarter, quarter, quarter, octal, quarter, octal, octal, octal, quarter, octal, quarter, connected_note(octal, octal), octal, quarter, octal, quarter, connected_note(octal, octal), point_note(quarter),
    quarter, quarter, quarter, quarter, octal, quarter, octal, octal, octal, quarter, octal, quarter, connected_note(octal, octal), octal, quarter, point_note(quarter), connected_note(octal, half)
  }, //Cantina band
  {
    octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, half, half,
    octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, half, half,
    octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, half, quarter, quarter
  } //Pokemon Theme*/
};

//songs available to be played
const float songs_frequencies[1][61] =
{
	{
		123.47, 164.81, 196.00, 185.00, 164.81, 246.94, 220.00, 185.00, 164.81, 196.00, 185.00, 155.56,
		123.47, 164.81, 196.00, 185.00, 164.81, 246.94, 220.00, 185.00, 164.81, 196.00, 185.00, 155.56,
		123.47, 164.81, 196.00, 185.00, 164.81, 246.94, 220.00, 185.00, 164.81, 196.00, 185.00, 155.56,
		123.47, 164.81, 196.00, 185.00, 164.81, 246.94, 220.00, 185.00, 164.81, 196.00, 185.00, 155.56,
		123.47, 164.81, 196.00, 185.00, 164.81, 246.94, 220.00, 185.00, 164.81, 196.00, 185.00, 155.56
	}/*
	{
		notes[2][B], notes[3][E], notes[3][G], notes[3][Fs], notes[3][E], notes[3][B], notes[3][A], notes[3][Fs], notes[3][E], notes[3][G], notes[3][Fs], notes[3][Ds],
		notes[3][F], notes[2][B], notes[2][B], notes[3][E], notes[3][G], notes[3][Fs], notes[3][E], notes[3][B], notes[4][D], notes[4][Cs], notes[4][C], notes[3][Gs],
		notes[4][C], notes[3][B], notes[3][As], notes[2][As], notes[3][G], notes[3][E], notes[3][G], notes[3][B], notes[3][G], notes[3][B], notes[3][G], notes[4][D],
		notes[4][Cs], notes[4][C], notes[3][Gs], notes[3][G], notes[3][B], notes[3][As], notes[2][As], notes[2][B], notes[3][B], notes[3][G], notes[3][B], notes[3][G],
		notes[3][B], notes[3][G], notes[4][C], notes[3][B], notes[3][As], notes[3][Fs], notes[4][C], notes[3][B], notes[3][As], notes[2][As], notes[3][G], notes[3][E], pause
	}, //harry potter - hedwig
	{
		notes[3][E], notes[2][B], notes[3][C], notes[3][D], notes[3][C], notes[2][B], notes[2][A], notes[2][A], notes[3][C], notes[3][E], notes[3][D], notes[3][C],
		notes[2][B], notes[3][C], notes[3][D], notes[3][E], notes[3][C], notes[2][A], notes[2][A], notes[2][A], notes[2][B], notes[3][C], notes[3][D], notes[3][F],
		notes[3][A], notes[3][G], notes[3][F], notes[3][E], notes[3][C], notes[3][E], notes[3][D], notes[3][C], notes[2][B], notes[2][B], notes[3][C], notes[3][D],
		notes[3][E], notes[3][C], notes[2][A], notes[2][A], pause, notes[3][E], notes[3][C], notes[3][D], notes[2][B], notes[3][C], notes[2][A], notes[2][Gs],
		notes[2][B], pause, notes[3][E], notes[3][C], notes[3][D], notes[2][B], notes[3][C], notes[3][E], notes[3][A], notes[3][Gs], pause, pause, pause
	}, //Tetris
	{
		notes[3][E], notes[3][A], notes[3][E], notes[3][A], notes[3][E], notes[3][A], notes[3][E], pause, notes[3][Ds], notes[3][E], notes[3][E],
		notes[3][Ds], notes[3][E], notes[3][D], pause, notes[3][Cs], notes[3][D], notes[3][Cs], notes[3][C], notes[2][A], notes[3][E], notes[3][A],
		notes[3][E], notes[3][A], notes[3][E], notes[3][A], notes[3][E], pause, notes[3][Ds], notes[3][E], notes[3][D], pause, notes[3][D],
		notes[3][Cs], notes[3][D], notes[3][G], notes[3][F], notes[3][E], notes[3][D], notes[3][E], notes[3][A], notes[3][E], notes[3][A], notes[3][E],
		notes[3][A], notes[3][E], pause, notes[3][Ds], notes[3][E], notes[3][G], pause, notes[3][G], notes[3][E], notes[3][D], notes[3][C], notes[2][A]
	}, //Cantina band
	{
		notes[2][D], notes[2][D], notes[2][A], notes[2][D], notes[2][D], notes[2][As], notes[2][D], notes[2][D], notes[2][A], notes[2][D], notes[2][D], notes[2][Cs],
		notes[2][D], notes[2][D], notes[2][A], notes[2][D], notes[2][D], notes[3][Cs], notes[3][D], pause, notes[2][D], notes[2][D], notes[2][A], notes[2][D],
		notes[2][D], notes[2][As], notes[2][D], notes[2][D], notes[2][A], notes[2][D], notes[2][D], notes[2][Cs], notes[2][D], notes[2][D], notes[2][A], notes[2][D],
		notes[2][D], notes[3][Cs], notes[3][D], pause, notes[2][D], notes[2][D], notes[2][A], notes[2][D], notes[2][D], notes[2][As], notes[2][D], notes[2][D],
		notes[2][A], notes[2][D], notes[2][D], notes[2][Cs], notes[2][D], notes[2][D], notes[2][A], notes[2][D], notes[2][D], notes[3][Cs], notes[3][D], pause, pause
	} //Pokemon Theme*/
};

//speed of songs
const uint8_t PROGMEM song_speed[NUM_OF_SONGS] = {180, 144, 180, 190};

#endif
