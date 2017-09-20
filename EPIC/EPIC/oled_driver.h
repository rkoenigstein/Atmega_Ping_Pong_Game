#ifndef OLED_DRIVER
#define OLED_DRIVER

#include "uart_driver.h"
#include <stdlib.h>
#include <stdbool.h>


#define F_CPU 4915200 // Clock speed

#include <util/delay.h>

//how is it possible to write the whole screen with the given memory mapping (512bytes)?
// -> write half the display per cycle


//__attribute__((section (".oled_buf")));

void clear_buffer(void);
void print_buffer(void);
void ones_buffer(void);

void oled_init();
void oled_reset();
void oled_home();
void oled_goto_line(int line);
void oled_goto_column(int column, int length);
void oled_clear_line(int line);
void oled_clear();
void oled_pos(int line, int column);
void oled_print(char letter);
void oled_write_command(uint8_t command);
void oled_print_letter(char c);

void oled_test();

#endif