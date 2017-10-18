#include "uart_driver.h"


#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

//#include <avr/delay.h>


void main_init (void)
{
	uart_init(BAUDRATE);
	//can_init();
	sei();
}


int main(void)
 {
	//CAN_TEST_COM();
	main_init();
    while(1)
    {
		//CAN_TEST_COM();
       	//uart_putstring("HELLO\n");
       	printf("hello world\n");
		_delay_ms(1000);
    }
}