//UART driver

#include "uart_driver_2560.h"

#define MAX_STRING 1000 

//initialize uart to 9600 8N1 (9600 Baud/Bit rate, 8 Bits data, no parity, 1 stop bit
void uart_init(unsigned int ubrr)
{
	//set baudrate to 9600
	UBRR0H = (unsigned char) (ubrr>>8);
	UBRR0L = (unsigned char) ubrr;
	
	//enable receiver and transmitter
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	//UCSR0A &= (0<<U2X0);
	
	//set UCSRC as accessed register, set number of character size to 8
	UCSR0C = (3<<UCSZ00); //| (1<<URSEL0);
	//set number of stop bits to 1
	UCSR0C &= ~(1<<USBS0);
	//set connection to asynchronous
	UCSR0C &= ~(1<<UMSEL00);
	UCSR0C &= ~(1<<UMSEL01); 
	//disable parity mode
	UCSR0C &= ~(1<<UPM00);
	UCSR0C &= ~(1<<UPM01);
	fdevopen(uart_putc, uart_getc);
}

//send data to RS232
void uart_putc(unsigned char c)
{
	//wait while register is free
	while (!(UCSR0A & (1<<UDRE0)));
	
	//put character to USART data register
	UDR0 = c;
}

//receive data from RS232
unsigned char uart_getc(void)
{
	//wait while register is free
	while(!(UCSR0A & (1<<RXC0)));
	
	//get value from USART data register
	return UDR0;
}

//send string to RS232
//TODO WITHOUT MAX_STRING -> pointer 
void uart_putstring(unsigned char* name)
{
	int i;
	for(i = 0; i<MAX_STRING; i++)
	{
		if(name[i]==0)
			i=MAX_STRING+1;
		else
			uart_putc(name[i]);
	}
}

//TEST FUNCTIONS

void TEST_reciver_transmitter_string(void)
{
 uart_init(BAUDRATE);
 
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