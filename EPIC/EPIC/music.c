#include "music.h"
#include "music_notes.h"

bool playing = false;
uint8_t songnumber = 0;

float song_frequencies[SONG_SIZE];
float song_durations[SONG_SIZE];

uint8_t songspeed = 120;

bool restart = false;

void music_init(void)
{
  //set music pin as output
  MUSIC_OUT_PORT |= (1 << MUSIC_PIN);

  //set timer mode 14 (Fast PWM)
  TCCR5A |= (1 << COM5A1);
  TCCR5B |= (1 << WGM53);
  TCCR5B |= (1 << CS51); //prescaler set to 8
}

void play_song(void)
{

  //pwm used for oscillating buzzer in given note frequency
  //depending on the clock and prescaler set, the ICR register of the
  //timer has to be calculated for the given frequency and set for each new note1
  //the duration of the current note has to be calculated and you have to wait for
  //the calculated time (could be improved by not busy waiting, but using a second timer)
	
  init_song();
 

  uint16_t icr5_value = 0;

  //play all notes of the song
  
  
  for(uint16_t note_in_song = 0; note_in_song < SONG_SIZE; note_in_song++)
  {
	  //calculate ICR5 value from note frequency (f_PWM=f_clk/(f_note*2*prescaler))
	icr5_value = (uint16_t) (F_CPU / (song_frequencies[note_in_song] * 2.0 * PRESCALER));

	//set loudness by setting the duty cycle (approx. icr5_value/2 will lead to loud sounds)
	OCR5A = icr5_value/2;
	//set note
	ICR5H = (icr5_value >> 8);
	ICR5L = icr5_value;

		//calculate note duration in ms based on speed (speed in quarters)
		uint16_t duration = (DEFAULT_WHOLE_NOTE_DURATION / 4) //as speed is in quarters
							* (60.0 / songspeed) //time of a quarter note
							* song_durations[note_in_song]; //duration of current note

		variable_delay_in_ms(duration);

		//pause in between notes
		OCR5A = 0;
		_delay_ms(15); 
		
		if(!playing)
			return;
		if(restart)
		{
			note_in_song = 0;
			restart = false;
		}
	  }
 
  
  OCR5A = 0;
}

void variable_delay_in_ms(uint16_t counter) 
{
	while(counter--)
		_delay_ms(1);
}

void TEST_music(void)
{
  printf("Playing Tetris\n");
  songnumber = 7;
  play_song();
}

void setPlaying(bool play, int song)
{
	playing = play;
	songnumber = song;
	restart = true;
	init_song();
}

void init_song(void)
{
	 for(int i = 0; i < SONG_SIZE; i++)
	 {
		 song_durations[i] = pgm_read_float(&songs_durations[songnumber][i]);
		 song_frequencies[i] = pgm_read_float(&songs_frequencies[songnumber][i]);
	 }

	songspeed = pgm_read_byte(&song_speed[songnumber]);
}