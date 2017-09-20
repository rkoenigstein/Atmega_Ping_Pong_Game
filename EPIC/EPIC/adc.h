//ADC driver

//filter for sliders:
//cutoff frequency: f = 11.254Hz
//slope: -20dB (just one pole in the filter)
#ifndef ADC
#define ADC

#include <avr/io.h>
#include <avr/interrupt.h>
#include <uart_driver.h>

//initialize MCU to work with interrupts
void adc_init(void);

char ADC_read(char channel);





#endif