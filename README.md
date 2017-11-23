# Atmega_Ping_Pong_Game

This repo contains code of a student project at Byggern at NTNU Trondheim. The scope of the project was to develop an embedded system for a Ping Pong game. The system consists of two nodes, one for the control of the motor, solenoid and servo and some other minor tasks and one for the major control logic and the user input. The two nodes are connected by a CAN bus. 

Node 1 consist of a breadboard, which we assembled from an atmega162, ADC, SRAM, GAL, CAN Transceiver, CAN controller, RS232 controller and a latch, and a USB multifunction board with a joystick, two touch sliders and two touch buttons as user input. The user input is passed from node 1 via the CAN bus to node 2 to update the PD motor controller and steer the servo and the solenoid. 

Node 2 is an Arduino Mega2560 (based on an atmel atmega2560 microcontroller), an I/O board and some peripherals for reading an IR sensor to count the score, a motor box and encoder and some neccessary circuitry for the servo and the solenoid.

The OLED display on the USB multifunction board is used to display a simple menu to choose what action to take (play songs, games, adjust settings,...) and the respective visual function feedback. 

Besides the control of the actual Ping Pong game, the possibility to play songs through a PWM output of the Arduino Mega2560 to a buzzer on the USB multifunction board, an easiy graphic library for the OLED and a graphical ping pong game are implemented.

To compile the code for the ATMEGA2560 microcontroller, pass the command line argument "-D ATMEGA2560" to the compiler, so that this macro is getting defined and the code for the ATMEGA2560 chosen 
