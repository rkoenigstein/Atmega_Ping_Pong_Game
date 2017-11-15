#ifndef PINGPONG_H_
#define PINGPONG_H_

#include "Parameters.h"
#include "can_driver.h"

/* play the main ping pong game */
void playPingPong(void);

/* send slider positions to node 2 */
void sendSliderPos(void);

/* send button states to node 2 */
void sendButton(void);

/* send joystick position to node 2 */
void sendJoyPos(void);

#endif