#include "timer_driver.h"

int current_top = (TOP-BOTTOM) / 2;

void timer_init(void)
{
	//set timer mode 14 (Fast PWM)
	TCCR3A |= (1 << WGM31) | (1 << COM3A1);
	TCCR3A &= ~(1 << WGM30);
	TCCR3B |= (1 << WGM32);
	TCCR3B |= (1 << WGM33);
	ICR3 = PERIOD;
	OCR3A = BOTTOM + (TOP - BOTTOM) / 2;

	//clock prescaler -> internal clock divided by 1024
	TCCR3B |= (1 << CS32);
	TCCR3B &= ~(1 << CS31);
	TCCR3B &= ~(1 << CS30);

	DDRE |= (1 << PE3);
}
