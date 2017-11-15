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
#include "MCP2515.h"

#define F_CPU 4915200 // Clock speed
#include <util/delay.h>

//#include "graphic.h"

MenuNode* menu_main;

JOY_POS joy_pos;
uint8_t score = 0;

uint8_t current_selection = 0;

bool highscore_activated = true;

uint8_t highscore[7] = { 0, 0, 0, 0, 0, 0, 0 };

void main_init(void)
{
	uart_init();
	sram_init();
	adc_init();
	USB_init();
	can_init();
	sei();
	oled_init();
	menu_main = getMenuRoot();
	printf("INIT DONE\n");
}

int main(void)
{
	main_init();
	
	//Optimization is in O3 because mallox cant allocate more memory for menus when playPingPong
	//is added to the menu as the memory gets too full and fragmented for malloc
	// -> ASK TUTUOR ON FRIDAY AND USE OTHER STUFF THAT WORKS
	
	//say hello to the guy in front of the display
	sayHello();

	//TEST_graphic();
	//_delay_ms(2000);
	//oled_test();
	

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

/*void send_song_CAN(uint8_t song)
{
	can_message song_msg = { .id = PLAY_SONG, .length = 1, .data = {song} };
	can_message_send(song_msg);
}

void song_harry_potter(void)
{
	send_song_CAN(HARRY_POTTER);
}

void song_cantina_band(void)
{
	send_song_CAN(CANTINA_BAND);
}

void song_pokemon(void)
{
	send_song_CAN(POKEMON);
}

void song_tetris(void)
{
	send_song_CAN(TETRIS);
}*/

void showHighscore(void)
{
	/*position pos = { .page = 0, .column = 1 };
	print_string_to_buffer("HIGHSCORE", pos);
	pos.page++;
	char place[1];
	char high[7];

	//prepare strings
	for(int i = 0; i < 8; i++)
	{
		char entry[16];
		strcpy(entry, "No. ");
		strcpy(entry, itoa(i, place[i], 10));
		strcpy(entry, ": ");
		strcpy(entry, itoa(highscore[i], high[i], 10));
		print_string_to_buffer(entry, pos);
		pos.page++;
	}
	print_buffer();*/
}

void resetHighscore(void)
{
	/*for(int i = 0; i < 8; i++)
		highscore[i] = 0;*/
}

void storeHighscore(void)
{
	/*position pos = { .page = 0, .column = 1 };
	print_string_to_buffer("Highscore is", pos);
	pos.page++;
	if(highscore_activated)
	{
		print_string_to_buffer("activated. To", pos);
		pos.page++;
		print_string_to_buffer("deactivate,", pos);
	}
	else
	{
		print_string_to_buffer("deactivated.", pos);
		pos.page++;
		print_string_to_buffer("To activate,", pos);
	}

	pos.page++;
	print_string_to_buffer("press left", pos);
	pos.page++;
	print_string_to_buffer("button.", pos);
	while(!JOY_button(0));
	highscore_activated = !highscore_activated;*/
}
void handleCANmessage(can_message can_msg)
{
	switch(can_msg.id)
	{
		case(SCORE):
		{
			if(can_msg.length != 1)
			{
				//printf("WRONG length of CAN message for SCORE\n");
				return;
			}
			score = can_msg.data[0];
		}
		default:
		{
			//printf("Unkwnon CAN message \n");
		}break;
	}
	
}

ISR(INT0_vect)
{
	//clear interrupt bits for rx buffer 0
	mcp_write(MCP_CANINTF, MCP_RX0IF & 0x00);
	
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
	
	//allow new message to be received into the buffer
	mcp_write(MCP_CANINTF, MCP_RX0IF & 0x00);
	

	handleCANmessage(can_msg);
}