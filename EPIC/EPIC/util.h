#ifndef UTIL_H_
#define UTIL_H_

#include "Parameters.h"
#include "strings.h"
#include <avr/pgmspace.h>
#include <stdio.h>

/* grab string from PROGMEM */
void getStringFromMem(char string[MAX_STRING_LENGTH], uint8_t id)
{
	strcpy_P(string, (PGM_P)pgm_read_word(&(string_table[id])));
}

#endif