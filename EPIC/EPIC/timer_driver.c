#include "timer_driver.h"

int current_top = (TOP-BOTTOM) / 2;

void timer_init(void)
{
	//set timer mode 14 (Fast PWM)
	TCCR4A |= (1 << WGM41) | (1 << COM4A1);
	TCCR4A &= ~(1 << WGM40);
	TCCR4B |= (1 << WGM42);
	TCCR4B |= (1 << WGM43);
	ICR4 = PERIOD;
	OCR4A = BOTTOM + (TOP - BOTTOM) / 2;

	//clock prescaler -> internal clock divided by 1024
	TCCR4B |= (1 << CS42);
	TCCR4B &= ~(1 << CS41);
	TCCR4B &= ~(1 << CS40);

	DDRH |= (1<<PH3);
}
