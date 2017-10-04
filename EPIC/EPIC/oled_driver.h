#ifndef OLED_DRIVER
#define OLED_DRIVER

#include "menu.h"
#include <stdlib.h>
#include <string.h>


#define F_CPU 4915200 // Clock speed
#define MAX_STRING_LENGTH 50
#define N 128 // display columns
#define M 8 // display pages for lines (8x8)

#include <util/delay.h>

//how is it possible to write the whole screen with the given memory mapping (512bytes)?
// -> write half the display per cycle


//__attribute__((section (".oled_buf")));

typedef struct position{
	uint8_t page;   //0-7
	uint8_t column; //0-127
	} position;

//initialize OLED display for page addressing mode starting in the top left corner
void oled_init();

//just a function call of oled_init()
void oled_reset();

//clears buffer and prints buffer to the display
void oled_clear();

//prints buffer to OLED display
void print_buffer(void);

//prints an 8bit column to the current OLED position
void oled_print(uint8_t data);

//clears buffer (set all buffer entries to 0
void clear_buffer(void);

//set all buffer entries to high
void ones_buffer(void);

//set the current page, which the OLED writes to
void oled_set_page(uint8_t page);

//write command to OLED controller
void oled_write_command(uint8_t command);

//write a string to 
void print_string_to_buffer(char* word, position pos);

//test function flashing OLED and writing test output to the display
void oled_test(void);

//prints blobs to the display
void printBlobs(void);

//prints greetings to the display
void printGreetings(void);

//prints current menu entries on the OLED
void printMenu(MenuNode* menu_entries);

//say hello to the guy in front of the display
void sayHello(void);

//prints buffer to serial output
void print_buffer_to_serial(void);

//print selection arrow
void print_selection(uint8_t page);

#endif