#include "Parameters.h"
#ifdef ATMEGA2560
	#define F_CPU 16000000
#else
	#define F_CPU 4915200
#endif
#include <util/delay.h>
#include "ir_driver.h"
#include "data_fit.h"

void ir_init(void)
{
	//enable ADC and set prescaler of 128
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

	//set AVCC as reference voltage
	ADMUX &= ~(1 << REFS1);
	ADMUX |= (1 << REFS0);

	selectADCChannel();
}

int getIRValue(void)
{
	uint8_t value[10];

	for(int i = 0; i < 10; i++)
	{
		//select the ADC channel
		selectADCChannel();

		//start ADC conversion
		ADCSRA |= (1 << ADSC);

		//wait until conversion is finished
		while(ADCSRA & (1 << ADSC));

		value[i] = ADC;
		_delay_us(1);
	}

	return data_fit(value, 10, 1, 3, 2);
}

void selectADCChannel(void)
{
		//select input channel as A0
		ADMUX &= ~(1 << MUX4) & ~(1 << MUX3) & ~(1 << MUX2) & ~(1 << MUX1) & ~(1 << MUX0);
		ADCSRB &= ~(1 << MUX5);
}
