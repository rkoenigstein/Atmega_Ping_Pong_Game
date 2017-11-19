#ifndef SRAM
#define SRAM

#include <avr/io.h>

#ifdef ATMEGA2560
	#define F_CPU 16000000
#else
	#define F_CPU 4915200
#endif
#include <util/delay.h>

//define latch enable pin
#define LE 1

/* initializes SRAM memory by activating external memory and releasing the JTAG pins from memory mapping */
void sram_init(void);

/* TEST FUNCTIONS for correct SRAM functioning and address decoding */
void TEST_write_adress(void);
void TEST_SRAM_test(void);
void TEST_GAL(void);
void TEST_ADC(void);

#endif
