#include "oled_driver.h"
#include "fonts.h"
#include "uart_driver.h"
#include <stdbool.h>

volatile uint8_t* oled_buffer=0x1800;

void oled_init()
{
	oled_write_command(0xae);        //  display  off
	oled_write_command(0xa1);        //segment  remap
	oled_write_command(0xda);        //common  pads  hardware:  alternative
	oled_write_command(0x12);
	oled_write_command(0xc8);        //common output scan direction:com63~com0
	oled_write_command(0xa8);        //multiplex  ration  mode:63
	oled_write_command(0x3f);
	oled_write_command(0xd5);        //display divide ratio/osc. freq. mode
	oled_write_command(0x80);
	oled_write_command(0x81);        //contrast  control
	oled_write_command(0x50);
	oled_write_command(0xd9);        //set  pre-charge  period
	oled_write_command(0x21);
	oled_write_command(0x20);        //Set  Memory  Addressing  Mode
	oled_write_command(0x02);		 //page addressing mode
	oled_write_command(0xdb);        //VCOM  deselect  level  mode
	oled_write_command(0x30);
	oled_write_command(0xad);        //master  configuration
	oled_write_command(0x00);
	oled_write_command(0xa4);        //out  follows  RAM  content
	oled_write_command(0xa6);        //set  normal  display
	oled_write_command(0xaf);        //  display  on	
	
	//set display offset
	oled_write_command(0xd3);
	oled_write_command(1);
	//set display start line
	oled_write_command(0x40);
	//set page start address
	oled_write_command(0xb0);
	//set the lower start column address
	oled_write_command(0);
	//set the upper start column address
	oled_write_command(127);
	
	clear_buffer();
	print_buffer();	
}

void oled_reset()
{
	oled_init();
}

void oled_clear()
{
	clear_buffer();
	print_buffer();
}

void print_buffer(void)
{
	oled_set_page(0);
	for(uint8_t i = 0; i < M; i++)
	{
		for(uint8_t j = 0; j < N; j++)
		{
			oled_print(oled_buffer[i*128+j]);
		}
		i < M ? oled_set_page(i+1) : oled_set_page(0);
	}
}

void oled_print(uint8_t data)
{
	volatile uint8_t* oled = 0x1200;
	*oled = data;
}

void clear_buffer(void)
{
	for(int i = 0; i < M; i++)
		for(int j = 0; j < N; j++)
		{
			oled_buffer[i*128+j] = 0x00;
		}
}

void ones_buffer(void)
{
	for(int i = 0; i < M; i++)
		for(int j = 0; j < N; j++)
		{	
			oled_buffer[i*128+j]=0xFF;
		}
}

void oled_set_page(uint8_t page)
{
	//set page start address
	oled_write_command(0xb0 | page);
	//set the lower start column address
	oled_write_command(0);
	//set the upper start column address
	oled_write_command(127);
}

void oled_write_command(uint8_t command)
{
	volatile uint8_t* _command = 0x1000;
	*_command = command;
}

void print_string_to_buffer(char* word, position pos)
{
	uint8_t i = 0;
	
	uint8_t col = pos.column;
	
	while (word[i] != '\0')
	{
		for (uint8_t j = 0; j < 8; j++) {
			*(oled_buffer + (pos.page<<7)+col) = pgm_read_byte(&font8[word[i]-32][j]);
			col++;
		}
		i++;
	}
}

void print_selection(uint8_t page)
{
	position pos = { .column = 120, .page = page};
	print_string_to_buffer("<", pos);
	print_buffer();
}

void oled_test()
{
	while(1)
	{
		ones_buffer();
		print_buffer();
		_delay_ms(2000);
		clear_buffer();
		print_buffer();
		_delay_ms(2000);
		position pos = { .page=1, .column = 5};
		print_string_to_buffer("hello_world", pos);
		print_buffer();
		_delay_ms(2000);
	}
}

void printBlobs(void)
{
	
}

void printGreetings(void)
{
	int counter = 0;
	position pos = {.page = 3, .column = 2};
	print_string_to_buffer("I want to greet ", pos);
	pos.page++;
	print_string_to_buffer("grandma, because", pos);
	pos.page++;
	print_string_to_buffer(" she is soooooooo pretty", pos);
	print_buffer();
	_delay_ms(1000);
}

void printMenu(MenuNode* menu_entries)
{
	clear_buffer();
	if(menu_entries)
	{
		for(int i = 0; i < menu_entries->m_num_submenus; i++)
		{
			if(menu_entries->m_submenus)
			{
				//TODO check if num submenus < 8
				position pos = { .page = i, .column = 2 };
				print_string_to_buffer(menu_entries->m_submenus[i]->m_content.title, pos);
			}
			else
				printf("NULL submenu\n");
		}
		print_buffer();		
	}	
	else
	{
		printf("empty menu pointer detected\n");
	}
}

void sayHello(void)
{
	clear_buffer();
	print_buffer();
	_delay_ms(2000);
	position pos = { .page = 0, .column =0 };
	print_string_to_buffer(" .------------. ", pos);
	pos.page++;
	print_string_to_buffer(" | Ping Pong! | ", pos);
	pos.page++;
	print_string_to_buffer(" `------------' ", pos);
	pos.page++;
	print_string_to_buffer("       ^        ", pos);
	pos.page++;
	print_string_to_buffer("       |  (\\_/) ", pos);
	pos.page++;
	print_string_to_buffer("       |__(O.o) ", pos);
	pos.page++;
	print_string_to_buffer("          (> <) ", pos);
	print_buffer();	
	_delay_ms(2000);
	clear_buffer();
	print_buffer();
}

void print_buffer_to_serial(void)
{
	for(int i = 0; i < M; i++)
	{
		for(int j = 0; j < N; j++)
		{
			printf("%d ", oled_buffer[i*N+j]);
		}
		printf("\n");
	}
}