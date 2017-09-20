//SRAM functions
#ifndef SRAM
#define SRAM

#define F_CPU 4915200 // Clock speed
#include <util/delay.h>
#include <avr/io.h>
#include "uart_driver.h"

#define LE 1 //define latch enable pin
//Initialize SRAM memory
void sram_init(void);

//TEST FUNCTIONS
void TEST_write_adress (void);
void TEST_SRAM_test(void);
void TEST_GAL(void);
void TEST_ADC(void);






#endif