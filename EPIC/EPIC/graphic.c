#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "joystick_driver.h"
#include "oled_driver.h"
#include "graphic.h"
#include "song_handler.h"

#ifdef ATMEGA2560
	#define F_CPU 16000000
#else
	#define F_CPU 4915200
#endif
#include <util/delay.h>

volatile uint8_t* display_buffer = (uint8_t *) 0x1800;

uint8_t full = 0;

/* takes the Ly vlaue of a rectangle and convert it to a char */
uint8_t Ly_2_char(int start, int Ly)
{
    uint8_t res = 0;
    int i = 0;
    for(i = start; i < Ly; i++)
        res |= (1 << i);
    return res;
}

/* calculates the position the char column in memory */
int start_calc(POS rect)
{
    return rect.y % 8;
}

/* calculates the number of bits to be put at one in the current page in a char column */
int bit_page_calc(RECT rect)
{
    int bit_page = 0;
    bit_page = abs(rect.Ly - (start_calc(rect.pos)));
    return bit_page;
}

void draw_rectangle_buffer(RECT rect)
{
    POS current;

    for(int i = rect.pos.x; i < rect.Lx + rect.pos.x; i++)
      for(int j = rect.pos.y; j < rect.Ly + rect.pos.y; j++)
      {
		current.x = i;
		current.y = j;
		switch(rect.full)
		{
			case(FULL):
			{
				draw_one_bit_buffer(current);
				break;
			}
			case(RECT_EMPT):
			{
				if(((i == rect.pos.x) || (j == rect.pos.y)) || ((i == rect.Lx + rect.pos.x - 1) || (j == rect.Ly + rect.pos.y - 1)))
				draw_one_bit_buffer(current);
				break;
			}
			case(TRI_EMPT):
			{
				if(((i == rect.pos.x) && (j == rect.pos.y)) || ((i == rect.Lx + rect.pos.x - 1) && (j == rect.Ly + rect.pos.y - 1)) || (full == 1))
				draw_one_bit_buffer(current);
				break;
			}
		}
     }
}

void draw_one_bit_buffer(POS bit)
{
    uint8_t res = 0;
    uint8_t start = 0;
	if(bit.y > 63 || bit.y < 0 || bit.x > 127 || bit.x < 0)
	{
		printf("POINT X=%d and y=%d OUTSIDE SCREEN\n", bit.x, bit.y);
		return;
	}
    start = start_calc(bit);
    res |= (1 << start);
	  display_buffer[(int) bit.y / 8 * N + bit.x] |= res;
}

void draw_triangle_buffer(TRI tri)
{
    RECT rect;
	int i = 0;
    rect.pos.x = tri.pos.x;
    rect.pos.y = tri.pos.y;
    rect.full = tri.full;
	full = 1;
    switch (tri.ori)
    {
        case RIGHT:
        {
            rect.Lx = 1;
            rect.Ly = tri.l;
			i = rect.Ly;
            do
            {
                draw_rectangle_buffer(rect);
				full = 0;
                rect.Ly -= 2;
				i -= 2;
                rect.pos.y++;
                rect.pos.x++;
            }
            while(i > 0);
            break;
        }
        case LEFT:
        {
            rect.Lx = 1;
            rect.Ly = tri.l;
            i = rect.Ly;
			do
            {
                draw_rectangle_buffer(rect);
				full = 0;
                rect.Ly -= 2;
				i -= 2;
                rect.pos.y++;
                rect.pos.x--;
            }
            while(i > 0);
            break;
        }
        case DOWN:
        {
            rect.Ly = 1;
            rect.Lx = tri.l;
			i = rect.Lx;
            do
            {
                draw_rectangle_buffer(rect);
				full = 0;
                rect.Lx -= 2;
				i -= 2;
                rect.pos.y++;
                rect.pos.x++;
            }
            while(i > 0);
            break;
        }
        case UP:
        {
            rect.Ly = 1;
            rect.Lx = tri.l;
            i = rect.Lx;
			do
            {
                draw_rectangle_buffer(rect);
				full = 0;
                rect.Lx -= 2;
				i -= 2;
                rect.pos.y--;
                rect.pos.x++;
            }
            while(i > 0);
            break;
        }
        default:
            break;
    }
}

void TEST_graphic(void)
{
	clear_buffer();
	print_buffer();
	RECT rect;
	rect.pos.x = 0;
	rect.pos.y = 0;
	rect.Lx = 10;
	rect.Ly = 10;
	rect.full = RECT_EMPT;
	draw_rectangle_buffer(rect);
	rect.pos.x = 105;
	rect.pos.y = 7;
	rect.full = FULL;
	draw_rectangle_buffer(rect);
	TRI tri;
	tri.pos.x = 33;
	tri.pos.y = 33;
	tri.l = 20;
	tri.ori = RIGHT;
	tri.full = TRI_EMPT;
	draw_triangle_buffer(tri);
	tri.ori = DOWN;
	tri.pos.y = 43;
	tri.pos.x = 10;
	tri.full = FULL;
	draw_triangle_buffer(tri);
	draw_triangle_buffer(tri);
	print_buffer();
	_delay_ms(2000);
}

void animations(void)
{
	send_song_CAN(HARRY_POTTER);
	
	clear_buffer();
	position strin;
	strin.column = 4;
	strin.page = 3;
	
	print_string_to_buffer("HAVE FUN WITH", strin);
	strin.page++;
	print_string_to_buffer("SQUARES AND", strin);
	strin.page++;
	print_string_to_buffer("TRIANGLES", strin);
	
	while(JOY_getPosition().dir != NEUTRAL);

	TRI tri;
	tri.pos.x = 33;
	tri.pos.y = 0;
	tri.l = 10;
	tri.ori = RIGHT;
	tri.full = FULL;
	draw_triangle_buffer(tri);
	
	RECT rect;
	rect.pos.x = 0;
	rect.pos.y = 0;
	rect.Lx = 10;
	rect.Ly = 10;
	rect.full = RECT_EMPT;
	draw_rectangle_buffer(rect);
	
	print_buffer();
	_delay_ms(2000);
	
	while (JOY_getPosition().dir != UP)
	{
		clear_buffer();
		tri.pos.x++;
		if(tri.pos.x + tri.l == 120)
		{
			tri.pos.x = 33;
			tri.pos.y = 33;
			tri.l = 20;
			if(tri.full == FULL)
				tri.full = TRI_EMPT;
			else
				tri.full = FULL;
			tri.ori++;
			if(tri.ori == DOWN)
				tri.ori = LEFT;
		}
		draw_triangle_buffer(tri);
		
		rect.pos.x += 2;
		rect.pos.y++;
		if(rect.pos.y + rect.Ly == 50)
		{
			rect.pos.x = 0;
			rect.pos.y = 0;
			rect.Lx = 10;
			rect.Ly = 10;
			if(rect.full == FULL)
				rect.full = RECT_EMPT;
			else
				rect.full = FULL;
		}
		draw_rectangle_buffer(rect);
		
		print_buffer();
		_delay_ms(10);	
	}
	
	send_stop_CAN();
}
