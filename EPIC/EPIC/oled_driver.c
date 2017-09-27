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

void print_string_to_buffer(char* word, uint8_t length, position pos)
{
	uint8_t mystring[128*length];
	convertStringToFont(word, length, mystring);
	memcpy(oled_buffer + (pos.page<<7)+pos.column, mystring, 8*length);
}

void convertStringToFont(char* myword, uint8_t mylength, uint8_t mystring[])
{
	for(int j = 0; j < mylength; j++)
	{
		for(int i = 0; i < 8; i++)
		{
			mystring[j*8+i] = (PGM_P)pgm_read_byte(&font8[myword[j]-32][i]);			
		}
		//printf("%d~\n", j);
	}
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
		print_string_to_buffer("hello_world", 11, pos);
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
	while(1)
	{
		position pos = {.page = 4, .column = counter++};
		print_string_to_buffer("I want to greet my mom, because she is soooo nice. I want to greet my grandma, because she is soooo pretty. I want to say hello to my teacher, because he is soooo bright. I want to say hello to my friend Peter, because he is soooo friendly. ", 235, pos);
		_delay_ms(50);
	}
}

void printMenu(menu* menu_entries)
{
	printf("Menu num submenus: %d\n", menu_entries->num_of_submenus);
	for(int i = 0; i < menu_entries->num_of_submenus; i++)
	{
		position pos = { .page = i, .column = 2 };
		printf("Menu title: %s\n", menu_entries->menu_title);
		print_string_to_buffer(menu_entries->submenu[i]->menu_title, menu_entries->title_length, pos);
		print_buffer();
	}
	
}

void sayHello(void)
{
	clear_buffer();
	print_buffer();
	_delay_ms(2000);
	position pos = { .page = 0, .column =0 };
	print_string_to_buffer(" .------------. ", 16, pos);
	pos.page++;
	print_string_to_buffer(" | Ping Pong! | ", 16, pos);
	pos.page++;
	print_string_to_buffer(" `------------' ", 16, pos);
	pos.page++;
	print_string_to_buffer("        ^       ", 16, pos);
	pos.page++;
	print_string_to_buffer("        |  (\\_/) ", 16, pos);
	pos.page++;
	print_string_to_buffer("        |__(O.o) ", 16, pos);
	pos.page++;
	print_string_to_buffer("           (> <) ", 16, pos);
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