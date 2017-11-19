#include "pingpong.h"
#include "oled_driver.h"
#include "joystick_driver.h"
#include "Parameters.h"
#include "can_driver.h"
#include "song_handler.h"

JOY_POS joy_pos, old_joy_pos;
SLID slid_pos, old_slid_pos;

static int score = 0;

void playPingPong(void)
{		
	char scorestring[15];
	
	can_message can_msg = { .id = START_PING_PONG, .length = 0 };
	can_message_send(can_msg);
	_delay_ms(10);
	
	clear_buffer();
	position pos;
	position scorepos = { .page = 4, .column = 2 };
	pos.page = 1;
	pos.column = 2;
	print_string_to_buffer("PINGPONG GAME", pos);
	pos.page++;
	print_string_to_buffer("LEFT SLID: leave", pos);
	
	score = 0;	

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
		
		sprintf(scorestring, "Score: %d", score);
		print_string_to_buffer(scorestring, scorepos);
		print_buffer();
		
		old_joy_pos = joy_pos;
		old_slid_pos = slid_pos;	
		
		if(SLID_getPosition().l < 10)
		{
			_delay_ms(10);
			can_message can_msg = { .id = STOP_PING_PONG, .length = 0 };
			can_message_send(can_msg);
			_delay_ms(10);
			return;			
		}
	}
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

void resetScore(void)
{
	score = 0;
}

void setScore(int newscore)
{
	score = newscore;
}

void sendCANGameWithoutIR(void)
{
	can_message can_msg = { .id = WITHOUT_IR, .length = 0 };
	can_message_send(can_msg);
	printf("CAN STOP IR sent\n");
}

void sendCANGameWithIR(void)
{
	can_message can_msg = { .id = WITH_IR, .length = 0 };
	can_message_send(can_msg);
	printf("CAN START IR sent\n");
}

void irSettings(void)
{
	clear_buffer();
	position pos = { .page = 2, .column = 2 };
	char string[MAX_STRING_LENGTH];
	for(int i = 0; i < 3; i++)
	{
		for (uint8_t i = 0; i < MAX_STRING_LENGTH; i++)
		string[i] = 0;
		getStringFromMem(string, 36 + i);
		print_string_to_buffer(string, pos);
		pos.page++;
	}
	print_buffer();
	
	while(1)
	{
		_delay_ms(50);
		//without this printf the function directly closes and goes back to its previous entry
		//printf("joy z : %d\n", JOY_getPosition().y);
		if(JOY_getPosition().y > 250)
		{
			while(JOY_getPosition().dir != NEUTRAL);
			_delay_ms(10);
			sendCANGameWithIR();
			_delay_ms(10);
			return;
		}
		_delay_ms(50);
		if(JOY_getPosition().y < 10)
		{
			while(JOY_getPosition().dir != NEUTRAL);
			_delay_ms(10);
			sendCANGameWithoutIR();
			_delay_ms(10);
			return;
		}
		_delay_ms(50);
	}
}