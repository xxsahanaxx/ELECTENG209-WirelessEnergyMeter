#include "led.h"

void led_toggle()
{
	if(PIND & (1<<2))
	{
		CLEAR_LED;
	}
	if(~PIND & (1<<2))
	{
		SET_LED;
	}
}