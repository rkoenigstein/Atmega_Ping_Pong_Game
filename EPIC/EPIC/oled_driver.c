#include "oled_driver.h"
#include "fonts.h"

#define N 128 // display columns
#define M 8 // display pages for lines (8x8)

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
	//set the lower start column address
	oled_write_command(0x0F);
	//set the upper start column address
	oled_write_command(0x1F);
	
	
	/*oled_write_command(0xd3);		// set display offset to 0
	oled_write_command(0x00);
	oled_write_command(0x40);		//set display start line to 0
	oled_goto_column(0,128);*/
	oled_clear();
	
	clear_buffer();
	
}

void clear_buffer(void)
{
	int result = 0;
	for(int i = 0; i < M; i++)
		for(int j = 0; j < N; j++)
		{
			result = i << 7;
			*(oled_buffer+result+j) = 0x00;
		}
}

void ones_buffer(void)
{
	int result=0;
	for(int i = 0; i < M; i++)
		for(int j = 0; j < N; j++)
		{
			result = i<<7;	
			*(oled_buffer+result+j)=0xFF;
		}
		
}

void print_buffer(void)
{
	int result = 0;
	for(int i = 0; i < M; i++)
	{
		for(int j = 0; j < N; j++)
		{
			result = i<<7;
			oled_print(*(oled_buffer+result+j));
			
			//printf("%d", *(oled_buffer+result+j));
		}
		oled_set_page(i);
		//printf("\n");
	}
}
//TODO Ask about Set lower column Sart adress for page adressing
//AND  Ask about Set Higher column Sart adress for page adressing
void oled_set_page(int i)
{
	//set page start address
	//oled_write_command(0x22);
	//oled_write_command(i);
	//oled_write_command(0x08);
	//set the lower start column address
	oled_write_command(i&(0b111));
	//set the upper start column address
	//uint8_t res = i+16;
	oled_write_command(1i);
}

void oled_reset()
{

}

void oled_home()
{
	
}

void oled_goto_line(int line)
{
	if(line > 0 && line < 65)
	{
		oled_write_command(0x40 + line - 1);
	}
	else
	{
		printf("Line parameter must be in between 1 and 64\n");
	}
}

void oled_write_command(uint8_t command)
{
	volatile uint8_t* _command = 0x1001;
	*_command = command;
}

void oled_goto_column(int column, int length)
{
	if(column > 0 && column < 129)
	{
		oled_write_command(0x21);
		oled_write_command(column-1);
		oled_write_command(column+length-1);
	}
	else
	{
		printf("Column parameter must be in between 1 and 128\n");
	}
}

void oled_clear_line(int line)
{
	//oled_goto_line(line);
	//oled_goto_column(1, 128);
	for(int i = 1; i < 128*64+1; i++)
	{
		oled_print(0);
	}
}

void oled_clear()
{
	oled_goto_line(1);
	oled_goto_column(1, 128);
	for(int i = 1; i < 128*64+1; i++)
	{
		oled_print(0);
	}
}

void oled_pos(int line, int column)
{
	oled_goto_line(line);
	oled_goto_column(column, 128);
}

void oled_print(char letter)
{
	volatile uint8_t* oled = 0x1200;
	*oled = letter;
}

void oled_print_letter(char c)
{
	c -=32;
	for(int i = 0; i < 8; i++)
	{
		oled_print((PGM_P)pgm_read_byte(&font8[c][i]));
	}	
}



void oled_test()
{
	//oled_pos(30,40);
	//oled_goto_column(1,128);
	/**int i = 0;
	while(1)
	{
		for(int j = 1; j < 129;j++)
		{
			oled_print(0);
			_delay_ms(50);
			oled_print(0xFF);
		}
		if(i==65)i=1;
	}*/
	
	while(1)
	{
		clear_buffer();
		print_buffer();
		_delay_ms(2000);
		ones_buffer();
		print_buffer();
		//oled_goto_line(0);
		/*for(int i = 0; i < 8; i++)
		{
			oled_print(font8[3][i]);
		}*/
		//char ch = '#';
		//oled_print_letter(ch);
		/*oled_print(font8[3][0]);
		oled_print(font8[3][1]);
		oled_print(font8[3][2]);
		oled_print(font8[3][3]);
		oled_print(font8[3][4]);
		oled_print(font8[3][5]);
		oled_print(font8[3][6]);
		oled_print(font8[3][7]);*/
		/*oled_print(0b00011000);
		oled_print(0b00011000);
		oled_print(0b01111110);
		oled_print(0b00111100);
		oled_print(0b00011000);
		oled_print(0b00011000);
		oled_print(0b00011000);
		oled_print(0b01111110);
		oled_print(0b00111100);
		oled_print(0b00011000);
		oled_print(0);
		oled_print(0);
		oled_print(0);*/
		
		_delay_ms(2000);
	}
}