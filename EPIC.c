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


//initialize uart to 9600 8N1 (9600 Baud/Bit rate, 8 Bits data, no parity, 1 stop bit
void init_uart(unsigned int ubrr);

//send data to RS232
void uart_putc(unsigned char c);

//receive data from RS232
unsigned char uart_getc();

void uart_init(unsigned int ubrr)
{
	//set baudrate to 9600
	UBRR1H = (unsigned char) (ubrr>>8); 
	UBRR1L = (unsigned char) ubrr;
	//enable receiver and transmitter
	UCSR1B = (1<<RXEN1)|(1<<TXEN1);
	//set UCSRC as accessed register, set number of stop bits to 1, set number of character size to 8
	UCSR1C = (1<<URSEL1)|(0<<USBS1)|(3<<UCSZ01);
}

void uart_putc(unsigned char c)
{
	
	//wait while register is free
	while (!(UCSR1A & (1<<UDRE1)));
	
	//put character to USART data register
	UDR1 = c;
}

unsigned char uart_getc(void)
{
	//wait while register is free
	while(!(UCSR1A & (1<<RXC1)));
	
	//get value from USART data register
	return UDR1;
}

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

