/*
 * EPIC.c
 *
 * Created: 06.09.2017 10:32:31
 *  Author: roberko
 */ 

#define F_CPU 4915200 // Clock speed



//connection of usb board

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart_driver.h"
#include "sram.h"
#include "adc.h"
#include "oled_driver.h"

void main_init (void)
{
	uart_init(BAUDRATE);
	sram_init();
	adc_init();
	JOY_init();
	sei();	
	oled_init();
}

int main(void)
{
	
	main_init();
	oled_test();
	/**while(1)
	{
		oled_test();
		_delay_ms(40);
	}
	while(1)
	{
	char result = ADC_read(7);
	printf("%d\n",result);
	_delay_ms(100);	
	}*/
	//while(1);
	
	//TEST_USB_BOARD();
	//TEST_GAL();
	//TEST_ADC();
	//TEST_SRAM_test();
   //TEST_write_adress();
   return 0;
}