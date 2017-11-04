/* filter for sliders:
 * cutoff frequency: f = 11.254Hz
 * slope: -20dB (just one pole in the filter) */
#ifndef ADC_DRIVER
#define ADC_DRIVER

#include <avr/io.h>
#include <avr/interrupt.h>
#include <uart_driver.h>

/* enable interrupt connected to the ADC */
void adc_init(void);

/* read from specified ADC channel */
char ADC_read(char channel);

#endif
