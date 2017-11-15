#ifndef STRINGS_H_
#define STRINGS_H_

#include <avr/pgmspace.h>

const char s_root[] PROGMEM = "root";
const char s_games[] PROGMEM = "Games";
const char s_pingpong[] PROGMEM = "PingPong";
const char s_pingpang[] PROGMEM = "PingPang";
const char s_highscore[] PROGMEM = "Highscore";
const char s_settings[] PROGMEM = "Settings";
const char s_store_highscore[] PROGMEM = "Store Highscore";
const char s_reset_highscore[] PROGMEM = "Reset Highscore";
const char s_calibrate_joy[] PROGMEM = "Calib Joystick";
const char s_calibrate_slid[] PROGMEM = "Calib Sliders";
const char s_left_slid[] PROGMEM = "Left Slider";
const char s_right_slid[] PROGMEM = "Right Slider";
const char s_songs[] PROGMEM = "Songs";
const char s_harry_potter[] PROGMEM = "Harry Potter";
const char s_tetris[] PROGMEM = "Tetris";
const char s_cantina_band[] PROGMEM = "Cantina Band";
const char s_pokemon[] PROGMEM = "Pokemon";
const char s_thumb1[] PROGMEM = "      /|        ";
const char s_thumb2[] PROGMEM = "     | \\         ";
const char s_thumb3[] PROGMEM = "  ____\\ \\  _____";
const char s_thumb4[] PROGMEM = " (____)  `|     ";
const char s_thumb5[] PROGMEM = "(____)|   |     ";
const char s_thumb6[] PROGMEM = " (____).__|     ";
const char s_thumb7[] PROGMEM = "  (___)__.|_____";
const char s_hello1[] PROGMEM = " .------------. ";
const char s_hello2[] PROGMEM = " | Ping Pong! | ";
const char s_hello3[] PROGMEM = " `------------' ";
const char s_hello4[] PROGMEM = "       ^        ";
const char s_hello5[] PROGMEM = "       |  (\\_/) ";
const char s_hello6[] PROGMEM = "       |__(O.o) ";
const char s_hello7[] PROGMEM = "          (> <) ";

PGM_P const string_table[] PROGMEM =
{
	s_root,
	s_games,
	s_pingpong,
	s_pingpang,
	s_highscore,
	s_settings,
	s_store_highscore,
	s_reset_highscore,
	s_calibrate_joy,
	s_calibrate_slid,
	s_left_slid,
	s_right_slid,
	s_songs,
	s_harry_potter,
	s_tetris,
	s_cantina_band,
	s_pokemon,
	s_thumb1,
	s_thumb2,
	s_thumb3,
	s_thumb4,
	s_thumb5,
	s_thumb6,
	s_thumb7,
	s_hello1,
	s_hello2,
	s_hello3,
	s_hello4,
	s_hello5,
	s_hello6,
	s_hello7
};


#endif