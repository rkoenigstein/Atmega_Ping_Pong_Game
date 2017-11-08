#ifndef UART_driver
#define UART_driver

#include <avr/io.h>
#include "Parameters.h"

#define BAUDR 9600
#ifdef ATMEGA2560
	#define FOSC 16000000
#else
	#define FOSC 4915200
#endif
#define MYUBRR FOSC/16/BAUDR-1

/* initialize uart to 9600 8N1 (9600 Baud/Bit rate, 8 Bits data, no parity, 1 stop bit */
void uart_init(void);

/* sends data to RS232 */
void uart_putc(unsigned char c);

/* receives data from RS232 */
unsigned char uart_getc(void);

/* sends string to RS232 */
void uart_putstring(unsigned char* name);

/* tests UART input and output */
void TEST_reciver_transmitter_string(void);

#endif
