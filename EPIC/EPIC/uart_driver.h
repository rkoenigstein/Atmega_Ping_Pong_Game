#ifndef UART_driver
#define UART_driver

#include "Parameters.h"

#include <avr/io.h>
#include <stdio.h>


#define BAUDR 9600

#ifdef ATMEGA2560
	#define F_CPU 16000000
#else
	#define F_CPU 4915200
#endif

#define MYUBRR F_CPU/16/BAUDR-1

#include <util/delay.h>

/* initialize uart to 9600 8N1 (9600 Baud/Bit rate, 8 Bits data, no parity, 1 stop bit */
void uart_init(void);

/* sends data to RS232 */
int uart_putc(uint8_t c);

/* receives data from RS232 */
int uart_getc(void);

/* sends string to RS232 */
void uart_putstring(char* name);

/* tests UART input and output */
void TEST_reciver_transmitter_string(void);

#endif
