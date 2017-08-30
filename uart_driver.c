//UART driver

#include "uart_driver.h"

#define set_bit(reg,bit) (reg |= (1 << bit))
#define clear_bit(reg,bit) (reg &= ~(1 << bit))
#define test_bit(reg,bit) (reg & (1 << bit))
#define loop_until_bit_is_set(reg,bit) while(!test_bit(reg,bit))
#define loop_until_bit_is_clear(reg,bit) while(test_bit(reg,bit))

//initialize uart to 9600 8N1 (9600 Baud/Bit rate, 8 Bits data, no parity, 1 stop bit
void init_uart()
{
	
}

//send data to RS232
void uart_putc(char c)
{
	DDRB |= 0b00010000;
	PORTB |= 0b00010000;
}

//receive data from RS232
char uart_getc(void)
{
		
}