#ifndef TIMER0_H_

#define TIMER0_H_

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

void timer0_init(void);
void TIMER_wait (uint32_t milliseconds);

#endif