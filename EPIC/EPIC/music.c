#include "music.h"

void music_init(void)
{
  //set PIN PA1 as output
  MUSIC_OUT_PORT |= (1 << MUSIC_PIN);
}

void play_song(uint8_t songnumber)
{
  //calculate number of notes in the song
  uint16__t song_size = sizeof(songs_frequencies[songnumber])/sizeof(float);

  //play all notes of the song
  for(uint16_t note_in_song = 0; note_in_song < song_size; note_in_song++)
  {
    //calculate note duration in ms based on the note's frequency
    unsigned float duration = 1000.0/songs_frequencies[songnumber][note_in_song];

    //play note for enough cycles to meet its duration/value (half, whole, quarter...) and speed (speed in quarters -> factor 4 to make 4s a whole note)
    for(uint16_t cycles = 0; cycles < songs_durations[songnumber][note_in_song]*1000.0*(60.0/(song_speed[songnumber]*4))/duration; cycles++)
    {
      //play note (half time off, half time on)
      MUSIC_PORT |= (1 << MUSIC_PIN);
      _delay_ms(duration/2);
      MUSIC_PORT &= ~(1 << MUSIC_PIN);
      _delay_ms(duration/2);
    }

    //pause in between notes for some time
    _delay_ms(songs_durations[songnumber][note_in_song] % duration);
  }
}

void TEST_music(void)
{
  printf("Playing Tetris\n");
  play_song(TETRIS);
  printf("Playing Harry Potter\n");
  play_song(HARRY_POTTER);
  printf("Playing Cantina Band\n");
  play_song(CANTINA_BAND);
  printf("Playing Pokemon\n");
  play_song(POKEMON);
}
