#include "joystick_driver.h"
#include "oled_driver.h"
#include "graphic.h"
#include <stdio.h>
#include <stdlib.h>

volatile uint8_t* display_buffer=0x1800;

//Takes the Ly vlaue of a rectangle and convert it to a char
uint8_t Ly_2_char (int start, int Ly)
{
    uint8_t res=0;
    int i=0;
    for(i=start; i<Ly; i++)
        res |=(1<<i);
    return res;
}

//Calculate the position the char column in memory
int start_calc(POS rect)
{
    return rect.y%8;
}
//Calculate the number of bits to be put at one in the current page in a char column
int bit_page_calc(RECT rect)
{
    int bit_page=0;
    bit_page=abs(rect.Ly-(start_calc(rect.pos)));
    return bit_page;
}

void draw_rectangle_buffer(RECT rect)
{
    int i=0;
    int j=0;
    int bit_page=0;//bit to be put at one in the current page in a column of 8
    bit_page=bit_page_calc(rect);
    
    for(i=rect.pos.x;i<rect.Lx;i++)
    {
        if(bit_page>=8)
            do
            {
                for(j=rect.pos.y; j<rect.Ly; j++)
                    display_buffer[i*N+j]=Ly_2_char(0,8);
                rect.pos.y+=8;
                rect.Ly-=8;
                bit_page=bit_page_calc(rect);
            }
            while(bit_page>=8);
        
        if(bit_page<8)
        {
            for(j=rect.pos.y; j<rect.Ly; j++)
                    display_buffer[i*N+j]=Ly_2_char(start_calc(rect.pos), rect.Ly);
        }
        
    }
}
void draw_one_bit_buffer(POS bit)
{
    uint8_t res=0;
    uint8_t start=0;
    start=start_calc(bit);
    res|=(1<<start);
    display_buffer[bit.y%8*N+bit.x]=res;
}

//draw a circle
void draw_circle_buffer(CIRC circ)
{
	/*int i=0;
    int j=0;
    
    for(i=circ.pos.x;i<circ.r;i++)
    {
        if(rect.Ly>8)
            do
            {
                for(j=rect.pos.y; j<rect.Ly; j++)
                    buffer[i*N+j]=Ly_2_char(8);
                rect.pos.y+=8;
                rect.Ly-=8;
            }
        while(rect.Ly>8);
        
        if(rect.Ly<8)
        {
            for(j=rect.pos.y; j<rect.Ly; j++)
                buffer[i*N+j]=Ly_2_char(rect.Ly);
        }
        
    }*/
}


//draw a triangle
void draw_triangle_buffer(TRI tri)
{
    RECT rect;
    rect.pos.x=tri.pos.x;
    rect.pos.y=tri.pos.y;
    rect.full=tri.full;
    switch (tri.ori) {
        case RIGHT:
        {
            rect.Lx=1;
            rect.Ly=tri.l;
            do
            {
                draw_rectangle_buffer(rect);
                rect.Ly-=2;
                rect.pos.y--;
                rect.pos.x++;
            }
            while(rect.Ly>0);
        }
        break;
        case LEFT:
        {
            rect.Lx=1;
            rect.Ly=tri.l;
            do
            {
                draw_rectangle_buffer(rect);
                rect.Ly-=2;
                rect.pos.y--;
                rect.pos.x--;
            }
            while(rect.Ly>0);
        }
        break;
        case UP:
        {
            rect.Ly=1;
            rect.Lx=tri.l;
            do
            {
                draw_rectangle_buffer(rect);
                rect.Lx-=2;
                rect.pos.y++;
                rect.pos.x++;
            }
            while(rect.Lx>0);
        }
        break;
        case DOWN:
        {
            rect.Ly=1;
            rect.Lx=tri.l;
            do
            {
                draw_rectangle_buffer(rect);
                rect.Lx-=2;
                rect.pos.y--;
                rect.pos.x++;
            }
            while(rect.Lx>0);
        }
            break;
        default:
            break;
    }	
}

void TEST_graphic(void)
{
	clear_buffer();
	RECT rect;
	rect.pos.x=2;
	rect.pos.y=2;
	rect.Lx=20;
	rect.Ly=20;
	draw_rectangle_buffer(rect);
	TRI tri;
	tri.pos.x=24;
	tri.pos.y=24;
	tri.l=5;
	tri.ori=RIGHT;
	//draw_triangle_buffer(tri);
	tri.ori=LEFT;
	//draw_triangle_buffer(tri);
	tri.pos.x=50;
	tri.pos.y=50;
	tri.l=7;
	tri.ori=UP;
	//draw_triangle_buffer(tri);
	tri.ori=DOWN;
	//draw_triangle_buffer(tri);
	POS bit = { .x = 20, .y = 50 };
	draw_one_bit_buffer(bit);
	bit.x = 0;
	bit.y = 0;
	draw_one_bit_buffer(bit);
	bit.x = 0;
	bit.y = 63;
	draw_one_bit_buffer(bit);
	bit.x = 127;
	bit.y = 0;
	draw_one_bit_buffer(bit);
	bit.x = 127;
	bit.y = 63;
	draw_one_bit_buffer(bit);
	print_buffer();
	print_buffer_to_serial(); 	
}