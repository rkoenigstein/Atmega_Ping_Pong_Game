#include "pingpong.h"
#include "oled_driver.h"
#include "joystick_driver.h"

JOY_POS joy_pos, old_joy_pos;
SLID slid_pos, old_slid_pos;

void playPingPong(void)
{
	clear_buffer();
	position pos;
	pos.page = 3;
	pos.column = 2;
	print_string_to_buffer("PINGPONG", pos);
	print_buffer();	

	while(1)
	{
		joy_pos = JOY_getPosition();
		slid_pos = SLID_getPosition();
		
		if(joy_pos.x > old_joy_pos.x + 10 || joy_pos.y > old_joy_pos.y + 10 || joy_pos.x < old_joy_pos.x - 10 || joy_pos.y < old_joy_pos.y - 10)
		{
			sendJoyPos();
			printf("CAN Joy sent\n");
		}
		
		_delay_ms(10);
		
		if(slid_pos.r > old_slid_pos.r + 10 || slid_pos.l > old_slid_pos.l + 10 || slid_pos.r < old_slid_pos.r - 10 || slid_pos.l < old_slid_pos.l - 10)
		{
			//printf("old l: %d, old r: %d, new l: %d, new r: %d\n", old_slid_pos.l, old_slid_pos.r, slid_pos.l,slid_pos.r);
			sendSliderPos();
			//printf("slid r: %d slid l: %d \n", slid_pos.l, slid_pos.r);
			printf("Can SLid sent\n");
		}
		
		_delay_ms(10);
		
		sendButton();
		
		_delay_ms(10);
		
		old_joy_pos = joy_pos;
		old_slid_pos = slid_pos;	
	}
	
	//send node2 to power down
	can_message button_msg = { .id = CAN_SLEEP, .length = 0 };
	can_message_send(button_msg);
}

void sendJoyPos(void)
{
	can_message joy_msg = { .id = JOY, .length = 3, .data = { joy_pos.x, joy_pos.y, joy_pos.dir } };
	can_message_send(joy_msg);
}

void sendButton(void)
{
	static uint16_t counter = 1;
	uint8_t data_b[8] = { R, 0, 0, 0, 0, 0, 0, 0 };

	if(!JOY_button(R) && !JOY_button(L))
	return;

	counter --;

	if(JOY_button(L))
	data_b[0] = L;

	if(counter == 0)
	{
		can_message button_msg = { .id = BUTTONS, .length = 1, .data[0] = data_b[0] };
		can_message_send(button_msg);
		counter = 10;
		printf("CAN Button sent\n");
	}
}

void sendSliderPos(void)
{
	can_message slid_msg = { .id = SLIDERS, .length = 2, .data = {slid_pos.r, slid_pos.l}};
	can_message_send(slid_msg);
}