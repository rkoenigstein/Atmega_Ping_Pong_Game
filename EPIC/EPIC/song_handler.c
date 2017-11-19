#include "song_handler.h"

void send_song_CAN(uint8_t song)
{
	can_message song_msg = { .id = START_SONG, .length = 1, .data[0] = song };
	can_message_send(song_msg);
	_delay_ms(10);
	printf("CAN START SONG\n");
}

void send_stop_CAN(void)
{
	can_message song_msg = { .id = END_SONG, .length = 0 };
	can_message_send(song_msg);
	_delay_ms(10);
	printf("CAN END SONG\n");
}

void song_harry_potter(void)
{
	displaySong(HARRY_POTTER);
	send_song_CAN(HARRY_POTTER);
	handleUserInput(HARRY_POTTER);
}

void song_cantina_band(void)
{
	displaySong(CANTINA_BAND);
	send_song_CAN(CANTINA_BAND);
	handleUserInput(CANTINA_BAND);
}

void song_pokemon(void)
{
	displaySong(POKEMON);
	send_song_CAN(POKEMON);
	handleUserInput(POKEMON);
}

void song_tetris(void)
{
	displaySong(TETRIS);
	send_song_CAN(TETRIS);
	handleUserInput(TETRIS);
}

void song_octaves(void)
{
	displaySong(IMPERIAL);
	send_song_CAN(IMPERIAL);
	handleUserInput(IMPERIAL);
}

void song_jingle_bells(void)
{
	displaySong(JINGLE_BELLS);
	send_song_CAN(JINGLE_BELLS);
	handleUserInput(JINGLE_BELLS);
}

void song_last_christmas(void)
{
	displaySong(LAST_CHRISTMAS);
	send_song_CAN(LAST_CHRISTMAS);
	handleUserInput(LAST_CHRISTMAS);
}

void song_merry_x_mas(void)
{
	displaySong(MERRY_X_MAS);
	send_song_CAN(MERRY_X_MAS);
	handleUserInput(MERRY_X_MAS);
}

void displaySong(uint8_t song)
{
	clear_buffer();
	position pos = { .page = 1, .column = 2 };
	char string[MAX_STRING_LENGTH];
	for (uint8_t i = 0; i < MAX_STRING_LENGTH; i++)
		string[i] = 0;
	switch(song)
	{
		case CANTINA_BAND:
		{
			getStringFromMem(string, 15);
			print_string_to_buffer(string, pos);
			break;
		}
		case HARRY_POTTER:
		{
			getStringFromMem(string, 13);
			print_string_to_buffer(string, pos);
			break;
		}
		case IMPERIAL:
		{
			getStringFromMem(string, 17);
			print_string_to_buffer(string, pos);
			break;
		}
		case MERRY_X_MAS:
		{
			getStringFromMem(string, 18);
			print_string_to_buffer(string, pos);
			break;
		}
		case POKEMON:
		{
			getStringFromMem(string, 16);
			print_string_to_buffer(string, pos);
			break;
		}
		case TETRIS:
		{
			getStringFromMem(string, 14);
			print_string_to_buffer(string, pos);
			break;
		}
		case JINGLE_BELLS:
		{
			getStringFromMem(string, 19);
			print_string_to_buffer(string, pos);
			break;
		}
		case LAST_CHRISTMAS:
		{
			getStringFromMem(string, 20);
			print_string_to_buffer(string, pos);
			break;
		}
	}
	pos.page++;
	for(uint8_t i = 0; i < MAX_STRING_LENGTH; i++)
		string[i] = 0;
	getStringFromMem(string, 45);
	print_string_to_buffer(string, pos);
	pos.page++;

	pos.page++;
	for(uint8_t i = 0; i < MAX_STRING_LENGTH; i++)
		string[i] = 0;
	getStringFromMem(string, 46);
	print_string_to_buffer(string, pos);
	pos.page++;
	for(uint8_t i = 0; i < MAX_STRING_LENGTH; i++)
		string[i] = 0;
	getStringFromMem(string, 47);
	print_string_to_buffer(string, pos);
	print_buffer();
}

void handleUserInput(uint8_t song)
{
	while(1)
		if(JOY_button(R))
		{
			send_stop_CAN();
			return;
		}
		_delay_ms(100);
}
