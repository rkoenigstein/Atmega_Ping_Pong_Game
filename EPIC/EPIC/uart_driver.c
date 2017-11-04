#include "uart_driver.h"

#define MAX_STRING 1000

void uart_init(void)
{
	//set baudrate to 9600
	UBRR0H = (unsigned char) (UBRR >> 8);
	UBRR0L = (unsigned char) UBRR;

	//enable receiver and transmitter
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	//set UCSRC as accessed register, set number of character size to 8
	UCSR0C = (1 << URSEL0) | (3 << UCSZ00);

	//set number of stop bits to 1
	UCSR0C &= (0 << USBS0);

	//set connection to asynchronous
	UCSR0C &= (0 << UMSEL0);

	//disable parity mode
	UCSR0C &= (0 << UPM00);
	UCSR0C &= (0 << UPM10);
	fdevopen(uart_putc, uart_getc);
}

void uart_putc(unsigned char c)
{
	//wait while register is free
	while (!(UCSR0A & (1 << UDRE0)));

	//put character to USART data register
	UDR0 = c;
}

unsigned char uart_getc(void)
{
	//wait while register is free
	while(!(UCSR0A & (1 << RXC0)));

	//get value from USART data register
	return UDR0;
}

void uart_putstring(unsigned char* name)
{
	int i;
	for(i = 0; i < MAX_STRING; i++)
	{
		if(name[i] == 0)
			i = MAX_STRING + 1;
		else
			uart_putc(name[i]);
	}
}

void TEST_reciver_transmitter_string(void)
{
 uart_init();

 unsigned char c;
 unsigned const char* hello_string = "Hello World";

 uart_putstring(hello_string);

 printf("Please enter something:");

 while(1)
 {
	 c = uart_getc();
	 uart_putc(c);
	 _delay_ms(100);
 }
}
