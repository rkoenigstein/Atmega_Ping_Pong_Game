/*
 * EPIC.c
 *
 * Created: 06.09.2017 10:32:31
 *  Author: roberko
 */ 

#define F_CPU 4915200 // Clock speed

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart_driver.h"
#include "sram.h"
#include "adc.h"
#include "oled_driver.h"
#include "menu.h"
//#include "graphic.h"


menu* menu_main;

void main_init (void)
{
	uart_init(BAUDRATE);
	sram_init();
	adc_init();
	JOY_init();
	sei();	
	oled_init();
	createMenu(menu_main);
}

int main(void)
{
	main_init();
	printf("INIT DONE\n");
	
	//say hello to the guy in front of the display
	sayHello();
	_delay_ms(2000);
	
	while(1)
	{
		//clear_buffer();
		//print_buffer();
		printMenu(menu_main);
		_delay_ms(200);
	}
	
	//TEST_graphic();
	//oled_test();
	//TEST_USB_BOARD();
	//TEST_GAL();
	//TEST_ADC();
	//TEST_SRAM_test();
    //TEST_write_adress();
   return 0;
}