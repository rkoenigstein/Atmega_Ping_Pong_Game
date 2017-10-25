#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <stdbool.h>

enum{RECT_EMPT, FULL, TRI_EMPT, CIRC_EMPT};
//define a position
struct pos
{
    int x;
    int y;
};
typedef struct pos POS;

//define position and dimension of a rectangle
struct rect
{
    POS pos;
    int Lx; //length in x
    int Ly; //length in y
    int full;//full or just the border
};
typedef struct rect RECT;

//define position and dimension of a circle
struct circ
{
    POS pos;
    int r; //radius of the circle
    int full;//full or just the border
};
typedef struct circ CIRC;

//define position dimension and orientation of a equilateral triangle
struct tri
{
    POS pos;
    int l; //length of the triangle
    int full;//full or just the border
    int ori;//orientation with enum
};
typedef struct tri TRI;


//draw a rectangle
void draw_rectangle_buffer(RECT rect);

//draw a circle
void draw_circle_buffer(CIRC circ);

//draw one bit
void draw_one_bit_buffer(POS bit);

//draw a triangle (45-degrees)
void draw_triangle_buffer(TRI tri);


//TEST
void TEST_graphic(void);

void TEST_animation(void);



#endif
