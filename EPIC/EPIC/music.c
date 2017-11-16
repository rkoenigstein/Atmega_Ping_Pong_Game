#include "music.h"
#include "music_notes.h"

void music_init(void)
{
  //set music pin as output
  MUSIC_OUT_PORT |= (1 << MUSIC_PIN);

  //set timer mode 14 (Fast PWM)
  TCCR5A |= (1 << COM5A1);
  TCCR5B |= (1 << WGM53);
  TCCR5B |= (1 << CS51); //prescaler set to 8
}

void play_song(uint8_t songnumber)
{

  //pwm used for oscillating buzzer in given note frequency
  //depending on the clock and prescaler set, the ICR register of the
  //timer has to be calculated for the given frequency and set for each new note1
  //the duration of the current note has to be calculated and you have to wait for
  //the calculated time (could be improved by not busy waiting, but using a second timer)

	/*int note1 = 4545;
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
	}*/


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

  uint16_t icr5_value = 0;

  //play all notes of the song
  for(uint16_t note_in_song = 0; note_in_song < song_size; note_in_song++)
  {
	  //calculate ICR5 value from note frequency (f_PWM=(f_note*2*prescaler)/f_clk)
    icr5_value = song_frequencies[note_in_song]*2*PRESCALER/F_CPU;

    //set loudness by setting the duty cycle (approx. icr5_value/2 will lead to loud sounds)
	  OCR5A = icr5_value/2;

	  //set note
	  ICR5H = (icr5_value >> 8);
	  ICR5L = icr5_value;

    //calculate note duration in ms based on speed (speed in quarters)
    uint16_t duration = DEFAULT_WHOLE_NOTE_DURATION / 4 //as speed is in quarters
                        * 60.0 / songspeed //time of a quarter note
                        * songs_durations[note_in_song]; //duration of current note

    _delay_loop_2(duration);

    _delay_ms(1); // 1ms pause in between two notes

    //play note for enough cycles to meet its duration/value (half, whole, quarter...) and speed (speed in quarters -> factor 4 to make 4s a whole note)
    //for(uint16_t cycles = 0; cycles < song_durations[note_in_song]*1000.0*(60.0/(songspeed*4))/duration; cycles++)
    //{
      //play note (half time off, half time on)
	  /*int delay = (int) duration/2;
      MUSIC_PORT |= (1 << MUSIC_PIN);
      _delay_loop_2(delay);
      MUSIC_PORT &= ~(1 << MUSIC_PIN);
      _delay_loop_2(delay);*/

	   //}

    //pause in between notes for some time
    //_delay_ms(5);
  }

  OCR5A = 0;
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
