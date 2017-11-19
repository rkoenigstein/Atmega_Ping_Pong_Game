#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <stdint.h>
#include <stdbool.h>

enum{FULL, RECT_EMPT, DESTROYED, TRI_EMPT, CIRC_EMPT};

//define a position
struct pos
{
    uint8_t x;
    uint8_t y;
};
typedef struct pos POS;

//define position and dimension of a rectangle
struct rect
{
    POS pos;
    uint8_t Lx;   //length in x
    uint8_t Ly;   //length in y
    uint8_t full; //full or just the border
};
typedef struct rect RECT;

//define position dimension and orientation of a equilateral triangle
struct tri
{
    POS pos;
    uint8_t l;    //length of the triangle
    uint8_t full; //full or just the border
    uint8_t ori;  //orientation with enum
};
typedef struct tri TRI;

/* draw a rectangle */
void draw_rectangle_buffer(RECT rect);

/* draw one bit */
void draw_one_bit_buffer(POS bit);

/* draw a triangle (45-degrees) */
void draw_triangle_buffer(TRI tri);

/* test simple graphic elements */
void TEST_graphic(void);

/* test animation */
void animations(void);

#endif
