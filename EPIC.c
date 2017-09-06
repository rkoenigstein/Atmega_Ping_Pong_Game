/*
 * EPIC.c
 *
 * Created: 30.08.2017 15:42:48
 *  Author: roberko
 */ 

//UART driver
#define BAUD 9600
#define F_CPU 4915200 // Clock speed
#define FOSC 4915200
#define BAUDRATE FOSC/16/BAUD-1

#include <util/delay.h>
//#include <avr/interrupt.h>
#include <avr/io.h>
#include "uart_driver.h"

int main(void)
{
	
	uart_init(BAUDRATE);
	
	unsigned char c;
	
    while(1)
    {
		//c = uart_getc();
        uart_putc('h');
		_delay_ms(100);
		uart_putc('e');
		_delay_ms(100);
		uart_putc('l');
		_delay_ms(100);
		uart_putc('l');
		_delay_ms(100);
		uart_putc('o');
		_delay_ms(100);
    }
}

