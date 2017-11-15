#include "music.h"
#include "music_notes.h"

void music_init(void)
{
  //set music pin as output
  MUSIC_OUT_PORT |= (1 << MUSIC_PIN);
  
  //set timer mode 14 (Fast PWM)
  TCCR5A |= (1 << COM5A1);
  TCCR5B |= (1 << WGM53);
  TCCR5B |= (1 << CS51);
}

void play_song(uint8_t songnumber)
{
	int note1 = 4545;
	int duration1 = 8;
	uint16_t delay = 10 * 1000;
		
	while(1)
	{
		printf("playing song\n");
		OCR5A = 80;
		ICR5H = (note1 >> 8);
		ICR5L = note1;
		for(int i=0;i<32-duration1;i++)
		{
			_delay_loop_2( delay );
		}
	}

  
  float song_frequencies[61];
  float song_durations[61];
  for(int i = 0; i < 61; i++)
  {
	  song_durations[i] = pgm_read_float(&songs_durations[songnumber][i]);
	  song_frequencies[i] = pgm_read_float(&songs_frequencies[songnumber][i]);
  }
  
  uint8_t songspeed = pgm_read_byte(&song_speed[songnumber]);
	  
  //calculate number of notes in the song
  uint16_t song_size = sizeof(song_frequencies)/sizeof(float);

  //play all notes of the song
  for(uint16_t note_in_song = 0; note_in_song < song_size; note_in_song++)
  {
	  //set loudness
	  OCR5A = 80;
	  
	  //set note
	  ICR5H = (note1 >> 8);
	  ICR5L = note1;

    //calculate note duration in ms based on the note's frequency
    uint16_t duration = 1000.0;

    //play note for enough cycles to meet its duration/value (half, whole, quarter...) and speed (speed in quarters -> factor 4 to make 4s a whole note)
    for(uint16_t cycles = 0; cycles < song_durations[note_in_song]*1000.0*(60.0/(songspeed*4))/duration; cycles++)
    {
      //play note (half time off, half time on)
	  int delay = (int) duration/2;
      MUSIC_PORT |= (1 << MUSIC_PIN);
      _delay_ms(delay);
      MUSIC_PORT &= ~(1 << MUSIC_PIN);
      _delay_ms(delay);
	 ICR1H = (duration >> 8);
	 ICR1L = duration;
    }

    //pause in between notes for some time
    //_delay_ms(5);
  }
}

void TEST_music(void)
{
  printf("Playing Tetris\n");
  play_song(TETRIS);
  /*printf("Playing Harry Potter\n");
  play_song(HARRY_POTTER);
  printf("Playing Cantina Band\n");
  play_song(CANTINA_BAND);
  printf("Playing Pokemon\n");
  play_song(POKEMON);*/
}
