#ifndef UART_driver_2560
#define UART_driver_2560

#include <avr/io.h>

#define BAUDRATE 9600
#define FOSC 16000000
#define UBRR FOSC/16/BAUDRATE-1

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
