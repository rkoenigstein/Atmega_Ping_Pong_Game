/*
 * EPIC.c
 *
 * Created: 06.09.2017 10:32:31
 *  Author: roberko
 */ 

#define F_CPU 4915200 // Clock speed

#include <util/delay.h>
#include <avr/io.h>
#include "uart_driver.h"
#include "sram.h"


int main(void)
{
	uart_init(BAUDRATE);
	sram_init();
	TEST_SRAM_test();
   //TEST_write_adress();
   return 25;
}