#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "Parameters.h"
#include "uart_driver.h"
#include "sram.h"
#include "adc_driver.h"
#include "oled_driver.h"
#include "can_driver.h"
#include "mcp_driver.h"
#include "menu.h"
#include "joystick_driver.h"
#include "spi_driver.h"
#include "game_1.h"
#include "pingpong.h"
#include "song_handler.h"
#include "MCP2515.h"

#define F_CPU 4915200 // Clock speed
#include <util/delay.h>

//#include "graphic.h"

MenuNode* menu_main;

JOY_POS joy_pos;

uint8_t current_selection = 0;

void main_init(void)
{
	cli();
	uart_init();
	printf("start init\n");
	sram_init();
	adc_init();
	USB_init();
	can_init();
	oled_init();
	menu_main = getMenuRoot();
	send_stop_CAN();
	can_message song_msg = { .id = STOP_PING_PONG, .length = 0 };
	can_message_send(song_msg);
	_delay_ms(10);
	sei();
	printf("INIT DONE\n");
}

int main(void)
{
	main_init();
	
	//say hello to the guy in front of the display
	sayHello();

	while(1)
	{

		joy_pos = JOY_getPosition();
		//printf("joy pos: %d, %d, %d \n", joy_pos.dir, joy_pos.x, joy_pos.y);
		
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

	//testCANconnection();
	//TEST_animation();
	//CAN_test();
	//TEST_graphic();
	//oled_test();
	//TEST_USB_BOARD();
	//TEST_GAL();
	//TEST_ADC();
	//TEST_SRAM_test();
	//TEST_write_adress();
  return 0;
}

/* test of CAN bus between node1 and node2 */
void testCANconnection(void)
{
	/*while(1)
	{
		can_message node_2;
		printf("Waiting for mz message\n");
		node_2 = can_data_receive();
		printf("Got it\n");
		printf("CAN id: %d, CAN data length: %d, CAN data: %c, %c, %c, %c \n",node_2.id, node_2.length, node_2.data[0], node_2.data[1], node_2.data[2], node_2.data[3]);
	}*/
}

ISR(INT0_vect)
{
	//handle CAN message
	can_message can_msg;
	
	//read upper 8 bit of id
	can_msg.id = mcp_read(MCP_RXB0SIDH) << 3;
	
	//read lower 8 bit of id
	can_msg.id |= mcp_read(MCP_RXB0SIDL) >> 5;
	
	//read length of CAN data
	can_msg.length = mcp_read(MCP_RXB0DLC);
	
	//read CAN data
	for(uint8_t i = 0; i < can_msg.length; i++)
		can_msg.data[i] = mcp_read(MCP_RXB0D0+i);
	
	switch(can_msg.id)
	{
		case(SCORE):
		{
			printf("Got new score: %d \n", can_msg.data[0]);
			setScore(can_msg.data[0]);
			break;
		}
		default:
		{
			printf("Unknown CAN message \n");
			break;
		}
	}
	
	//clear interrupt bits for rx buffer 0
	mcp_write(MCP_CANINTF, MCP_RX0IF & 0x00);
}