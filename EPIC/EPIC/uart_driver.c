#include "uart_driver.h"

#define MAX_STRING 1000

void uart_init(void)
{
	uint8_t ubrr = MYUBRR;
	
	//set baudrate to 9600
	UBRR0H = (uint8_t) (ubrr >> 8);
	UBRR0L = (uint8_t) ubrr;

	//enable receiver and transmitter
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

	//set UCSRC as accessed register, set number of character size to 8
	#ifdef ATMEGA2560
		UCSR0C |= (3 << UCSZ00);
	#else
		UCSR0C |= (1 << URSEL0) | (3 << UCSZ00);
	#endif

	//set number of stop bits to 1
	UCSR0C &= ~(1 << USBS0);

	//set connection to asynchronous
	#ifdef ATMEGA2560
		UCSR0C &= ~(1 << UMSEL00);
		UCSR0C &= ~(1 << UMSEL01);
	#else
		UCSR0C &= ~(1 << UMSEL0);
	#endif

	//disable parity mode
	UCSR0C &= ~(1 << UPM00);
	UCSR0C &= ~(1 << UPM10);
	
	fdevopen(uart_putc, uart_getc);
}

int uart_putc(uint8_t c)
{
	//wait while register is free
	while (!(UCSR0A & (1 << UDRE0)));

	//put character to USART data register
	UDR0 = c;
	return 0;
}

int uart_getc(void)
{
	//wait while register is free
	while(!(UCSR0A & (1 << RXC0)));

	//get value from USART data register
	return UDR0;
}

void uart_putstring(char* name)
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
	 /*uart_init();

	 char c;
	 char* hello_string = "Hello World";

	 uart_putstring(hello_string);

	 printf("Please enter something:");

	 while(1)
	 {
		 c = uart_getc();
		 uart_putc(c);
		 _delay_ms(100);
	 }*/
}
