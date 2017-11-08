#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#define ATMEGA2560

/* IDs for CAN messages */
enum CAN_IDS {JOY, SLIDERS, BUTTONS, CAN_SLEEP};

/* Right, left and direction for CAN message */
enum CAN_POS {R, L, DIR};

#endif