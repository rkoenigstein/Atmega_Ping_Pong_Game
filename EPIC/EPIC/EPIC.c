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

int main(void)
{
    uart_init(BAUDRATE);
    
    unsigned char c;
    unsigned const char* hello_string = "Hello World";
	
	uart_putstring(hello_string);
	
	fdevopen(uart_putc, uart_getc);
	
	printf("Please enter something:");
    
	while(1)
    {
	    c = uart_getc();
	    uart_putc(c);
	    _delay_ms(100);

    }
}