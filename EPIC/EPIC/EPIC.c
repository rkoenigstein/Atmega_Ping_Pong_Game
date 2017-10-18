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
#include "can_driver.h"
#include "mcp_driver.h"
#include "menu.h"
#include "joystick_driver.h"
#include "spi_driver.h"

//#include "graphic.h"


MenuNode* menu_main;
JOY_POS joy_pos;
uint8_t current_selection = 0;

void main_init (void)
{
	uart_init(BAUDRATE);
	sram_init();
	adc_init();
	JOY_init();
	can_init();
	sei();	
	oled_init();
	//menu_main = getMenuRoot();
	printf("INIT DONE\n");
	}
	
ISR(BADISR_vect)
{
	printf("getting random interrupts\n");
}

int main(void)
{
	main_init();
	
	//say hello to the guy in front of the display
	sayHello();
	
	
	/*can_message node_2;
	printf("Waiting for mz message\n");
	node_2=can_data_receive();
	printf("Got it\n");
	printf("CAN id: %d, CAN data length: %d, CAN data: %c, %c, %c, %c, %c \n",node_2.id, node_2.length, node_2.data[0], node_2.data[1], node_2.data[2], node_2.data[3],node_2.data[4], node_2.data[5]);*/
	
	//CAN_test();
	_delay_ms(1000);
	
	TEST_graphic();
		//_delay_ms(1000);	
	
	while(0)
	{
		
		joy_pos = JOY_getPosition();
		_delay_ms(10);
		
		switch(joy_pos.dir)
		{
			case UP:
			{
				current_selection = current_selection == 0 ? menu_main->m_num_submenus-1 : current_selection-1;
				getPreviousEntry(menu_main->m_submenus[current_selection]);
				break;
			}
			case RIGHT:
			{
				if(menuLevelDown(menu_main, current_selection)->m_num_submenus > 0)
				{
					menu_main = menuLevelDown(menu_main, current_selection);
					current_selection = 0;
				}
				else
				{
					if(menuLevelDown(menu_main, current_selection)->m_content.operation)
						menuLevelDown(menu_main, current_selection)->m_content.operation();
				}
				break;
			}
			case DOWN:
			{
				current_selection = current_selection == menu_main->m_num_submenus-1 ? 0 : current_selection+1;
				getNextEntry(menu_main->m_submenus[current_selection]);
				break;
			}
			case LEFT:
			{
				if(menu_main->m_parent)
				{
					menu_main = menuLevelUp(menu_main);
					current_selection = 0;
				}
				break;
			}
			default:
				break;
			
		}
		
		printMenu(menu_main);
		print_selection(current_selection);
		_delay_ms(300);
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