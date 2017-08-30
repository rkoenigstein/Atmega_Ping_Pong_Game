//UART driver
#define BAUDRATE 9600
#define F_CPU 4915200 // Clock speed
#define MYUBRR F_CPU/16/BAUDRATE-1

#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

//initialize uart to 9600 8N1 (9600 Baud/Bit rate, 8 Bits data, no parity, 1 stop bit
void init_uart(unsigned int ubrr);

//send data to RS232
void uart_putc(unsigned char c);

//receive data from RS232
unsigned char uart_getc();

void init_uart(unsigned int ubrr)
{
	UBRRH = (unsigned char) (ubrr>>8);
	UBRRL = (unsigned char) ubrr;
	UCSRB = (1<<RXEN)|(1<<TXEN);
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
	
}

void uart_putc(unsigned char c)
{
	while (!(UCSRA & (1<<UDRE)));
	
	UDR = c;
}

unsigned char uart_getc(void)
{
	while(!(UCSRA & (1<<RXC)));
	return UDR;	
}