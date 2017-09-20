//UART driver

#ifndef UART_driver
#define UART_driver

#define BAUD 9600
#define FOSC 4915200
#define BAUDRATE FOSC/16/BAUD-1

#include <avr/io.h>

//initialize uart to 9600 8N1 (9600 Baud/Bit rate, 8 Bits data, no parity, 1 stop bit
void uart_init(unsigned int ubrr);

//send data to RS232
void uart_putc(unsigned char c);

//receive data from RS232
unsigned char uart_getc(void);

//send string to RS232
void uart_putstring(unsigned char* name);

//TODO add read string function







//TEST FUNCTIONS
void TEST_reciver_transmitter_string(void);



#endif