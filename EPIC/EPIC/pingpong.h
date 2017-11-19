#ifndef PINGPONG_H_
#define PINGPONG_H_

#include <string.h>
#include <stdint.h>

/* play the main ping pong game */
void playPingPong(void);

/* send slider positions to node 2 */
void sendSliderPos(void);

/* send button states to node 2 */
void sendButton(void);

/* send joystick position to node 2 */
void sendJoyPos(void);

/* set new score received by CAN */
void setScore(int newscore);

/* game with IR */
void sendCANGameWithIR(void);

/* game without IR */
void sendCANGameWithoutIR(void);

/* menu in settings to activate or deactivate the IR sensor */
void irSettings(void);

/* returns highscore */
uint8_t* getHighscore(void);

#endif