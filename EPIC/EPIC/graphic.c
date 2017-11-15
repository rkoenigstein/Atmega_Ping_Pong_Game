#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "joystick_driver.h"
#include "oled_driver.h"
#include "graphic.h"

#ifdef ATMEGA2560
	#define F_CPU 16000000
#else
	#define F_CPU 4915200
#endif
#include <util/delay.h>

volatile uint8_t* display_buffer = (uint8_t *) 0x1800;

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
    int i = 0;
    int j = 0;
    POS current;

    for(i = rect.pos.x; i < rect.Lx + rect.pos.x; i++)
      for(j = rect.pos.y; j < rect.Ly + rect.pos.y; j++)
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
				if(((i == rect.pos.x) && (j == rect.pos.y)) || ((i == rect.Lx + rect.pos.x - 1) && (j == rect.Ly + rect.pos.y - 1)))
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

void draw_circle_buffer(CIRC circ) // DOESN'T WOOOOOORKKKK
{
  	POS current = circ.pos;
  	POS distance;
  	draw_one_bit_buffer(circ.pos);
  	int flag = 1;
  	do
  	{
  		distance.x = abs(current.x - circ.pos.x);
  		distance.y = abs(current.y - circ.pos.y);

  		draw_one_bit_buffer(current);

  		if(distance.x * distance.x + distance.y * distance.y > circ.r * circ.r)
  			flag++;

  		if(flag == 1){
  			current.x++;
  			current.y++;
  		}

  		current = circ.pos;
  		if(flag == 2){
  			current.x--;
  			current.y++;
  		}

  		current = circ.pos;
  		if(flag == 3){
  			current.x--;
  			current.y--;
  		}

  		current = circ.pos;
  		if(flag == 4){
  			current.x++;
  			current.y--;
  		}

  		current = circ.pos;
  	} while(flag > 4);
}

void draw_triangle_buffer(TRI tri)
{
    RECT rect;
	int i=0;
    rect.pos.x = tri.pos.x;
    rect.pos.y = tri.pos.y;
    rect.full = tri.full;
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
                rect.Lx -= 2;
				i -= 2;
                rect.pos.y--;
                rect.pos.x++;
            }
            while(i > 0);
            break;
        }
        default:
        {
            break;
        }
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
	rect.full = TRI_EMPT;
	draw_rectangle_buffer(rect);
	rect.pos.x = 105;
	rect.pos.y = 7;
	rect.full = FULL;
	draw_rectangle_buffer(rect);
	TRI tri;
	tri.pos.x = 33;
	tri.pos.y = 33;
	tri.l = 33;
	tri.ori = UP;
	tri.full = FULL;
	draw_triangle_buffer(tri);
	/*tri.ori = DOWN;
	tri.pos.y = 43;
	tri.pos.x = 70;
	tri.full = FULL;
	draw_triangle_buffer(tri);
	//draw_triangle_buffer(tri);*/
	/*CIRC circ;
	circ.pos.x = 70;
	circ.pos.y = 20;
	circ.r = 15;
	draw_circle_buffer(circ);*/
	POS bit = { .x = 20, .y = 50 };
	draw_one_bit_buffer(bit);
	bit.x = 0;
	bit.y = 0;
	draw_one_bit_buffer(bit);
	bit.x = 1;
	bit.y = 1;
	draw_one_bit_buffer(bit);
	bit.x = 2;
	bit.y = 2;
	draw_one_bit_buffer(bit);
	bit.x = 3;
	bit.y = 3;
	draw_one_bit_buffer(bit);
	bit.x = 4;
	bit.y = 4;
	draw_one_bit_buffer(bit);
	bit.x = 5;
	bit.y = 5;
	draw_one_bit_buffer(bit);
	bit.x = 6;
	bit.y = 6;
	draw_one_bit_buffer(bit);
	bit.x = 7;
	bit.y = 7;
	draw_one_bit_buffer(bit);
	bit.x = 8;
	bit.y = 8;
	draw_one_bit_buffer(bit);
	bit.x = 9;
	bit.y = 9;
	draw_one_bit_buffer(bit);
	bit.x = 10;
	bit.y = 10;
	draw_one_bit_buffer(bit);
	bit.x = 11;
	bit.y = 11;
	draw_one_bit_buffer(bit);
	print_buffer();
	_delay_ms(2000);
	//print_buffer_to_serial();
}
void TEST_animation(void)
{
	TRI tri;
	tri.pos.x = 128 / 2 - 15 / 2;
	tri.pos.y = 0;
	tri.l = 15;
	tri.ori = DOWN;
	int i = 0;

	draw_triangle_buffer(tri);

	for(i = 0; i < 63; i++)
	{
		//oled_init();
		clear_buffer();
		//print_buffer();
		tri.pos.y++;
		draw_triangle_buffer(tri);
		//printGreetings();
		print_buffer();
		_delay_ms(20);
	}


}
