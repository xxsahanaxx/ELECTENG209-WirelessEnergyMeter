#include <avr/io.h>
#include "interrupt.h"

void interrupt_init()
{
	//Interrupt Setups 1
	// sets interrupt on rising edge
	EICRA|=(1<<ISC01);
	EICRA|=(1<<ISC00);
	EIMSK|=(1<<INT0);

	//Interrupt Setups 2
	// sets interrupt on rising edge
	EICRA|=(1<<ISC11);
	EICRA|=(1<<ISC10);
	EIMSK|=(1<<INT1);
}