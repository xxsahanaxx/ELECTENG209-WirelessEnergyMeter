#include "timer0.h"
#include "led.h"

//initialises the timer with a 1 millisecond range
void timer0_init()
{
	//CTC mode and prescaler of 256
	TCCR0B = (1<<CS01) | (1<<CS00);
	
	// Compare on Match Output A and B is disconnected
	TCCR0A |= 0b00000010;
	
	// The time measured would be 64 microseconds for every count. 
	OCR0A = 250;//crossing 16 counters would give us our period of approximately 1 millisecond
	
	// Timer interrupt enable
	//TIMSK0 |= (1<<OCIE0A);
}

void TIMER_wait (uint32_t milliseconds){
	uint32_t timer_overflows=0;
	TCNT0=0;
	
	while (timer_overflows<milliseconds){
		if ((TIFR0& (1<<OCF0A))!=0){
			timer_overflows++;
			TIFR0 |= (1<<OCF0A);
		}
	}
}

