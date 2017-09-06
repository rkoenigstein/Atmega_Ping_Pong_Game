//UART driver

#include "uart_driver.h"

#define MAX_STRING 1000 
#define set_bit(reg,bit) (reg |= (1 << bit))
#define clear_bit(reg,bit) (reg &= ~(1 << bit))
#define test_bit(reg,bit) (reg & (1 << bit))
#define loop_until_bit_is_set(reg,bit) while(!test_bit(reg,bit))
#define loop_until_bit_is_clear(reg,bit) while(test_bit(reg,bit))

//initialize uart to 9600 8N1 (9600 Baud/Bit rate, 8 Bits data, no parity, 1 stop bit
void uart_init(unsigned int ubrr)
{
	//set baudrate to 9600
	UBRR0H = (unsigned char) (ubrr>>8);
	UBRR0L = (unsigned char) ubrr;
	
	//enable receiver and transmitter
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	//set UCSRC as accessed register, set number of character size to 8
	UCSR0C = (1<<URSEL0)|(3<<UCSZ00);
	//set number of stop bits to 1
	UCSR0C &= (0<<USBS0);
	//set connection to asynchronous
	UCSR0C &= (0<<UMSEL0); 
	//disable parity mode
	UCSR0C &= (0<<UPM00);
	UCSR0C &= (0<<UPM10);
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
void uart_putstring(unsigned const char* name)
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