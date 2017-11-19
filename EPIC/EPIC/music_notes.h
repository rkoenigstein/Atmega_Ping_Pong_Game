#ifndef MUSIC_NOTES_H_
#define MUSIC_NOTES_H_

#include <avr/pgmspace.h>
//#include <stdint.h>

#define pause 0.00

#define whole 4.0
#define half 2.0
#define quarter 1.0
#define octal 0.5
#define sixteenth 0.25
#define zero 0.0

#define NUM_OF_SONGS 8

#define SONG_SIZE 134

#define point_note(x) ((x) * 1.5)
#define connected_note(x, y) ((x) + (y))

//music frequencies of notes according to http://www.phy.mtu.edu/~suits/notefreqs.html
#define C1	32.70
#define Cs1	34.65
#define D1	36.71
#define Ds1	38.89
#define E1	41.20
#define F1  43.65
#define Fs1	46.25
#define G1	49.00
#define	Gs1	51.91
#define A1	55.00
#define As1	58.27
#define H1	61.74
#define C2	65.41
#define Cs2	69.30 
#define D2	73.42 
#define Ds2	77.78 
#define E2	82.41 
#define F2	78.31 
#define Fs2	92.50 
#define G2	98.00 
#define	Gs2	103.83 
#define A2	110.00 
#define As2	116.54 
#define H2	123.47
#define C3	130.81 
#define Cs3	138.59 
#define D3	146.83 
#define Ds3	155.56 
#define E3	164.81 
#define F3	174.61 
#define Fs3	185.00 
#define G3	196.00 
#define	Gs3	207.65 
#define A3	220.00 
#define As3	233.08 
#define H3	246.94
#define C4	261.63
#define Cs4	277.18 
#define D4	293.66
#define Ds4	311.13 
#define E4	329.63 
#define F4	349.23 
#define Fs4	369.99 
#define G4	392.00 
#define	Gs4	415.30 
#define A4	440.00 
#define As4	466.16 
#define H4	493.88

//songs available to be played
const float songs_durations[NUM_OF_SONGS][SONG_SIZE] PROGMEM =
{
  {
    quarter, point_note(quarter), octal, quarter, half, quarter, point_note(half), point_note(half),
    point_note(quarter), octal, quarter, half, quarter, connected_note(point_note(half), half),
    quarter, point_note(quarter), octal, quarter, half, quarter, half, quarter, half, quarter, point_note(quarter),
    octal, quarter, half, quarter, connected_note(point_note(half), half), quarter, half, quarter, half, quarter, half, quarter, half,
    quarter, point_note(quarter), octal, quarter, half, quarter, connected_note(point_note(half), half), quarter,
    half, quarter, half, quarter, half, quarter, half, quarter, point_note(quarter), octal, quarter, half, quarter, connected_note(point_note(half), half), 
	quarter, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
	zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
	zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
	zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
	zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
	zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
	zero, zero
  }, //harry potter - hedwig
  {
    quarter, octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, octal, octal, point_note(quarter), octal, quarter, quarter, quarter, quarter,
    octal, octal, octal, point_note(quarter), octal, quarter, octal, octal, point_note(quarter), octal, quarter, octal, octal, quarter, octal, octal, quarter,
    quarter, quarter, quarter, quarter, quarter, half, half, half, half, half, half, half, quarter, quarter, half, half, half, half, quarter, quarter, half, half,
    quarter, octal, octal, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
	zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
	zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
	zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
	zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
	zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
	zero, zero
  }, //Tetris
  {
    quarter, quarter, quarter, quarter, octal, quarter, octal, octal, octal, quarter, octal, octal, octal, octal, octal, octal, octal, octal, point_note(quarter), connected_note(octal, half),
    quarter, quarter, quarter, quarter, octal, quarter, octal, octal, octal, quarter, octal, quarter, connected_note(octal, octal), octal, quarter, octal, quarter, connected_note(octal, octal), point_note(quarter),
    quarter, quarter, quarter, quarter, octal, quarter, octal, octal, octal, quarter, octal, quarter, connected_note(octal, octal), octal, quarter, point_note(quarter), 
	connected_note(octal, half), zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
	zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
	zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
	zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
	zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
	zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
	zero, zero
  }, //Cantina band
  {
    octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, half, half,
    octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, half, half,
    octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, octal, octal, quarter, half, quarter, 
	quarter, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
	zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
	zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
	zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
	zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
	zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
	zero, zero
  }, //Pokemon Theme
	/*{
		quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, 
		quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, 
		quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, 
		quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter,
		quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, 
		quarter, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, 
		zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
		zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
		zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
		zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
		zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
		zero, zero
	},*/ //Octaves
	{
		quarter, quarter, quarter, point_note(octal), sixteenth, quarter, point_note(octal), sixteenth,
		half, quarter, quarter, quarter, point_note(octal), sixteenth, quarter, point_note(octal),
		sixteenth, half, quarter, point_note(octal), sixteenth, quarter, point_note(octal), sixteenth,
		sixteenth, sixteenth, octal, octal, octal, quarter, point_note(octal), sixteenth,
		sixteenth, sixteenth, octal, octal, octal, quarter, point_note(octal), sixteenth,
		quarter, point_note(octal), sixteenth, half, quarter, point_note(octal), sixteenth, quarter,
		point_note(octal), sixteenth, sixteenth, sixteenth, octal, octal, octal, quarter,
		point_note(octal), sixteenth, sixteenth, sixteenth, octal, octal, octal, quarter,
		point_note(octal), sixteenth, quarter, point_note(octal), sixteenth, half, zero, zero, 
		zero, zero, zero, zero, zero, zero, zero, zero, 
		zero, zero, zero, zero, zero, zero, zero, zero, 
		zero, zero, zero, zero, zero, zero, zero, zero,
		zero, zero, zero, zero, zero, zero, zero, zero, 
		zero, zero, zero, zero, zero
	}, //Imperial March
	{
		quarter, quarter, octal, octal, octal, octal, quarter, quarter, quarter, quarter, octal, octal, 
		octal, octal, quarter, quarter, quarter, quarter, octal, octal, octal, octal, quarter, quarter, 
		octal, octal, quarter, quarter, quarter, half, quarter, quarter, quarter, quarter, half, quarter, 
		quarter, quarter, quarter, half, quarter, quarter, quarter, quarter, quarter, quarter, octal, octal, 
		quarter, quarter, quarter, half, quarter, quarter, octal, octal, octal, octal, quarter, quarter, 
		quarter, quarter, octal, octal, octal, octal, quarter, quarter, quarter, quarter, octal, octal, 
		octal, octal, quarter, quarter, octal, octal, quarter, quarter, quarter, half, zero, zero,
		zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
		zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
		zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
		zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero,
		zero, zero
	}, //Merry Christmas
	{
		octal, octal, octal, octal, quarter, octal, octal, octal, octal, octal, octal, quarter, 
		octal, octal, octal, octal, octal, octal, quarter, octal, octal, octal, octal, octal, 
		octal, quarter, octal, octal, octal, octal, octal, octal, quarter, octal, octal, octal, 
		octal, octal, octal, quarter, octal, octal, octal, octal, octal, octal, octal, octal, 
		octal, octal, octal, octal, octal, octal, point_note(quarter), octal, octal, octal, quarter, octal,
		octal, quarter, octal, octal, point_note(octal), sixteenth, point_note(quarter), octal, octal, octal, point_note(octal), sixteenth, 
		octal, octal, octal, sixteenth, sixteenth, octal, octal, octal, octal, quarter, quarter, octal, 
		octal, quarter, octal, octal, quarter, octal, octal, point_note(octal), sixteenth, point_note(quarter), pause, octal,
		octal, point_note(octal), sixteenth, octal, octal, octal, sixteenth, sixteenth, octal, octal, octal, octal, 
		point_note(quarter), zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, 
		zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, 
		zero, zero
	}, //Jingle Bells
	{
		point_note(quarter), connected_note(octal, octal), quarter, octal, octal, octal, octal, connected_note(octal, quarter),
		octal, octal, octal, octal, quarter, point_note(quarter), octal, octal, octal, octal, connected_note(octal, quarter), quarter,
		point_note(quarter), connected_note(octal, point_note(quarter)), octal, octal, octal, octal, connected_note(octal, quarter), octal, octal, octal, octal, connected_note(octal, octal),
		quarter, connected_note(octal, octal), point_note(quarter), half, point_note(quarter), connected_note(octal, octal), quarter, octal, octal, octal, octal, connected_note(octal, quarter),
		octal, octal, octal, octal, quarter, point_note(quarter), octal, octal, octal, octal, connected_note(octal, quarter), quarter, 
		point_note(quarter), connected_note(octal, point_note(quarter)), octal, octal, octal, octal, connected_note(octal, quarter), octal, octal, octal, octal, octal, 
		connected_note(octal, octal), quarter, connected_note(octal, octal), point_note(quarter), half, half, point_note(quarter), connected_note(octal, half), octal, octal, octal, octal, 
		quarter, quarter, connected_note(half, half), octal, octal, octal, octal, connected_note(whole, half), octal, octal, octal, octal, 
		whole, half, octal, octal, quarter, quarter, quarter, octal, octal, octal, octal, point_note(quarter), 
		connected_note(octal, sixteenth), sixteenth, connected_note(octal, quarter), octal, octal, octal, octal, octal, octal, octal, octal, octal, 
		octal, octal, connected_note(octal, octal), quarter, connected_note(octal, quarter), octal, sixteenth, connected_note(sixteenth, octal), octal, quarter, octal, octal, 
		octal, sixteenth, connected_note(sixteenth, octal), octal, quarter
	} //Last Christmas
};

//songs available to be played
const float songs_frequencies[NUM_OF_SONGS][SONG_SIZE] PROGMEM =
{
	{
		H2, E3, G3, Fs3, E3, H3, A3, Fs3, E3, G3, Fs3, Ds3,
		F3, H2, H2, E3, G3, Fs3, E3, H3, D4, Cs4, C4, Gs3,
		C4, H3, As3, As2, G3, E3, G3, H3, G3, H3, G3, D4,
		Cs4, C4, Gs3, G3, H3, As3, As2, H2, H3, G3, H3, G3,
		H3, G3, C4, H3, As3, Fs3, C4, H3, As3, As2, G3, E3, 
		pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, 
		pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, 
		pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause,
		pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause,
		pause
	}, //harry potter - hedwig
	{
		E3, H2, C3, D3, C3, H2, A2, A2, C3, E3, D3, C3,
		H2, C3, D3, E3, C3, A2, A2, A2, H2, C3, D3, F3,
		A3, G3, F3, E3, C3, E3, D3, C3, H2, H2, C3, D3,
		E3, C3, A2, A2, pause, E3, C3, D3, H2, C3, A2, Gs2,
		H2, pause, E3, C3, D3, H2, C3, E3, A3, Gs3, pause, pause,
		pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause,
		pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause,
		pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause,
		pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause,
		pause
	}, //Tetris
	{
		E3, A3, E3, A3, E3, A3, E3, pause, Ds3, E3, E3,
		Ds3, E3, D3, pause, Cs3, D3, Cs3, C3, A2, E3, A3,
		E3, A3, E3, A3, E3, pause, Ds3, E3, D3, pause, D3,
		Cs3, D3, G3, F3, E3, D3, E3, A3, E3, A3, E3,
		A3, E3, pause, Ds3, E3, G3, pause, G3, E3, D3, C3, A2,
		pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause,
		pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause,
		pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause,
		pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause,
		pause
	}, //Cantina band
	{
		D3, D3, A3, D3, D3, As3, D3, D3, A3, D3, D3, Cs3,
		D3, D3, A3, D3, D3, Cs4, D4, pause, D3, D3, A3, D3,
		D3, As3, D3, D3, A3, D3, D3, Cs3, D3, D3, A3, D3,
		D3, Cs4, D4, pause, D3, D3, A3, D3, D3, As3, D3, D3,
		A3, D3, D3, Cs3, D3, D3, A3, D3, D3, Cs4, D4, pause,
		pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause,
		pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause,
		pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause,
		pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause,
		pause
	}, //Pokemon Theme
	/*{
		pause, pause, pause, pause, pause, pause, pause, pause, pause, C2,	pause, D2, 
		pause, E2, pause, F2, pause, G2, pause, A2, pause, H2, pause, C3,	
		pause, D3, pause, E3, pause, F3, pause, G3, pause, A3, pause, H3, 
		pause, C4,	pause, D4, pause, E4, pause, F4, pause, G4, pause, A4, 
		pause, H4, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, 
		pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause,
		pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause,
		pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause,
		pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause,
		pause
	}, //Octaves*/
	{
		G3, G3, G3, E3, H3, G3, E3, H3,
		G3, D4, D4, D4, E4, H3, Fs3, E3,
		H3, G3, G4, G3, G3, G4, Fs4, F4,
		E4, Ds4, E4, pause, Gs3, Cs4, C4, H3, As3,
		A3, As3, pause, E3, Fs3, E3, G3,
		H3, G3, H3, D4, G4, G3, G3, G4,
		Fs4, F4, E4, Ds4, E4, pause, Gs3, Cs4,
		C4, H3, As3, A3, As3, pause, E3, Fs3,
		E3, H3, G3, E3, H3, G3, pause, pause,
		pause, pause, pause, pause, pause, pause, pause, pause,
		pause, pause, pause, pause, pause, pause, pause, pause,
		pause, pause, pause, pause, pause, pause, pause, pause,
		pause, pause, pause, pause, pause, pause, pause, pause,
		pause, pause, pause, pause, pause
	}, //Imperial
	{
		D3, G3, G3, A3, G3, Fs3, E3, E3, E3, A3, A3, H3, 
		A3, G3, Fs3, D3, D3, H3, H3, C4, H3, A3, G3, E3, 
		D3, D3, E3, A3, Fs3, G3, D3, G3, G3, G3, Fs3, Fs3,
		G3, Fs3, E3, D3, A3, H3, A3, G3, D4, D3, D3, D3, 
		E3, A3, Fs3, G3, D3, G3, G3, A3, G3, Fs3, E3, E3, 
		E3, A3, A3, H3, A3, G3, Fs3, D3, D3, H3, H3, C4, 
		H3, A3, G3, E3, D3, D3, E3, A3, E3, Fs3, pause, pause,
		pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause,
		pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause, pause,
		pause  		
	}, //Merry Christmas
	{
		D3, H3, A3, G3, D3, pause, D3, D3, H3, A3, G3, E3, 
		pause, E3, E3, C4, H3, A3, Fs3, pause, Fs3, D4, D4, C4, 
		A3, H3, pause, D3, D3, H3, A3, G3, D3, pause, D3, D3, 
		H3, A3, G3, E3, pause, E3, E3, C4, H3, A3, D4, D4, 
		D4, D4, E4, D4, C4, A3, G3, pause, H3, H3, H3, H3, 
		H3, H3, H3, D4, G3, A3, H3, pause, C4, C4, C4, C4, 
		C4, H3, H3, H3, H3, H3, A3, A3, H3, A3, D3, H3,
		H3, H3, H3, H3, H3, H3, D4, G3, A3, H3, pause, C4, 
		C4, C4, C4, C4, H3, H3, H3, H3, D4, D4, C4, A3, 
		G3		
	}, //Jingle Bells
	{
		A3, A3, G3, D3, A3, A3, H3, G3, E3, G3, A3, A3, 
		H3, G3, E3, Fs3, G3, Fs3, E3, pause, H3, A3, E3, H3,
		C4, H3, A3, pause, G3, Fs3, G3, G3, Fs3, G3, Fs3, D3, 
		pause, A3, A3, G3, D3, A3, A3, H3, A3, E3, G3, A3, 
		A3, H3, A3, E3, Fs3, G3, Fs3, E3, pause, H3, A3, E3, 
		H3,	C4, H3, A3, pause, G3, Fs3, G3, G3, Fs3, G3, Fs3, 
		D3, pause, D3, D4, D3, D3, E3, Fs3, G3, A3, G3, E3, 
		D4, H3, G3, E3, C3, E4, C4, A3, Fs3, D3, D4, C4, 
		H3, A3, pause, A3, A3, G3, pause, G3, D4, H3, A3, G3, 
		pause, A3, A3, A3, A3, G3, pause, G3, E4, E4, pause, H3, 
		H3, A3, G3, H3, E3, G3, A3, pause, H3, H3, H3, E3, 
		G3, A3
	} //Last Christmas
};

//speed of songs
const uint8_t PROGMEM song_speed[NUM_OF_SONGS] = {180, 144, 180, 190, 144, 144, 180, 100};

#endif
