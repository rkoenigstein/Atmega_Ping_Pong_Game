#include "adc_driver.h"

volatile int flag = 0;

void adc_init(void)
{
	//enabling adc interrupts
	GICR |= (1<<INT2);
}

char ADC_read(char channel)
{
	volatile int * adc_channel = (int *) 0x1400;
	adc_channel[0] = channel;
	char value;
	while(!flag);
	value = adc_channel[20];
	flag = 0;
	return value;
}

//interrupt service routine to notice when data available
ISR(INT2_vect)
{
	flag = 1;
}
