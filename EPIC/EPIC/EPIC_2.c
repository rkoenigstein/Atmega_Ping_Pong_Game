#include "uart_driver_2560.h"
#include "MCP2515.h"

#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

//#include <avr/delay.h>

#include "can_driver_2560.h"
#include "timer_driver.h"

typedef struct
{
	int x;
	int y;
	int dir;
} JOY_POS;

typedef struct
{
	int l;
	int r;
} SLID;

enum JOY_DIR {NEUTRAL,LEFT, RIGHT, UP, DOWN, LEFT_UP, LEFT_DOWN, RIGHT_UP, RIGHT_DOWN};

can_message can_msg;
JOY_POS current_joy_pos;
int cur_top = BOTTOM + (TOP-BOTTOM)/2;

enum CAN_IDS {JOY};

void main_init (void)
{
	uart_init(BAUDRATE);
	can_init();
	timer_init();
	sei();
	printf("INIT DONE\n");
}

update_OCR(uint8_t joy_x_pos)
{
	OCR4A = (uint8_t) calculateDutyCycle(joy_x_pos);	
}

int main(void)
 {
	main_init();
    while(1)
    {
		_delay_ms(100);
		can_msg = can_data_receive();
		
		switch(can_msg.id)
		{
			case JOY: 
			{
				current_joy_pos.x = can_msg.data[0];
				current_joy_pos.y = can_msg.data[1];
				current_joy_pos.dir = can_msg.data[2];
				update_OCR(current_joy_pos.x);
				printf("JOY x: %d, JOY y: %d, JOY dir: %d\n", current_joy_pos.x, current_joy_pos.y, current_joy_pos.dir);
				break;
			}
			default:
			{
				printf("CAN ID unknown\n");
				break;
			}
		}
		
    }
}