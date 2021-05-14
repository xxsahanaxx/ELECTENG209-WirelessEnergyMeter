#ifndef LED_H_

#define LED_H_

#include <avr/io.h>


#define SET_LED   PORTB |= (1<<PB5)
#define CLEAR_LED  PORTB &= ~(1<<PB5)

void led_toggle(void);

#endif