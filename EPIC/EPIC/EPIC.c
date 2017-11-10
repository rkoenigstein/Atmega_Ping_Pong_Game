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

#define F_CPU 4915200 // Clock speed
#include <util/delay.h>

//#include "graphic.h"

MenuNode* menu_main;
JOY_POS joy_pos, old_joy_pos;
SLID slid_pos, old_slid_pos;
uint8_t current_selection = 0;

bool highscore_activated = true;

uint16_t highscore[7] = { 0, 0, 0, 0, 0, 0, 0 };

void main_init(void)
{
	uart_init();
	sram_init();
	adc_init();
	USB_init();
	can_init();
	sei();
	oled_init();
	//menu_main = getMenuRoot();
	printf("INIT DONE\n");
	_delay_ms(1000);
	}

/* interrupt service routine catching undefined interrupts */
ISR(BADISR_vect)
{
	printf("Got undefined interrupts\n");
}

void sendJoyPos(void)
{
	can_message joy_msg = { .id = JOY, .length = 3, .data = {joy_pos.x, joy_pos.y, joy_pos.dir} };
	can_message_send(joy_msg);
}

void sendButton(void)
{
	uint8_t data_b = R;

	//printf("LEFT=%d, RIGHT=%d\n",JOY_button(L), JOY_button(R));
	if(!JOY_button(R) && !JOY_button(L))
		return;
	if(JOY_button(L))
		data_b = L;
	can_message button_msg = { .id = BUTTONS, .length = 1, .data = data_b};
	can_message_send(button_msg);
	printf("CAN Button sent\n");
}

void sendSliderPos(void)
{
	can_message slid_msg = { .id = SLIDERS, .length = 2, .data = {slid_pos.r, slid_pos.l}};
	can_message_send(slid_msg);
}

int main(void)
{
	main_init();

	//say hello to the guy in front of the display
	sayHello();

	while(1)
	{
		joy_pos = JOY_getPosition();
		slid_pos = SLID_getPosition();
		if(joy_pos.x > old_joy_pos.x + 10 || joy_pos.y > old_joy_pos.y + 10 || joy_pos.x < old_joy_pos.x - 10 || joy_pos.y < old_joy_pos.y - 10)
		{
			sendJoyPos();
			//printf("Sending ")
		}
		_delay_ms(10);
			sendButton();
		_delay_ms(10);
		if(slid_pos.r > old_slid_pos.r + 10 || slid_pos.l > old_slid_pos.l + 10 || slid_pos.r < old_slid_pos.r - 10 || slid_pos.l < old_slid_pos.l - 10)
			sendSliderPos();
		_delay_ms(10);
		old_joy_pos = joy_pos;
		old_slid_pos = slid_pos;
	}

	/*while(0)
	{

		joy_pos = JOY_getPosition();
		sendJoyPos();
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
	}*/

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
	while(1)
	{
		can_message node_2;
		printf("Waiting for mz message\n");
		node_2 = can_data_receive();
		printf("Got it\n");
		printf("CAN id: %d, CAN data length: %d, CAN data: %c, %c, %c, %c \n",node_2.id, node_2.length, node_2.data[0], node_2.data[1], node_2.data[2], node_2.data[3]);
	}
}

void send_song_CAN(uint8_t song)
{
	can_message song = { .id = PLAY_SONG, .length = 1, .data = {song} };
	can_message_send(song);
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
}

void showHighscore(void)
{
	position pos = { .page = 0, .column = 1 };
	print_string_to_buffer("HIGHSCORE", pos);
	pos.page++;
	char place[1];
	char high[7];

	//prepare strings
	for(int i = 0; i < 8; i++)
	{
		char entry[16];
		strcpy(entry, "No. ");
		strcpy(entry, itoa(i, place[i]));
		strcpy(entry, ": ");
		strcpy(entry, itoa(highscore[i], high[i]));
		print_string_to_buffer(entry, pos);
		pos.page++;
	}
	print_buffer();
}

void resetHighscore(void)
{
	for(int i = 0; i < 8; i++)
		highscore[i] = 0;
}

void storeHighscore(void)
{
	position pos = { .page = 0, .column = 1 };
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
	highscore_activated = !highscore_activated;
}
