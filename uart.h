#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


void usart_init(uint32_t ubrr);
void usart_transmit_byte(uint8_t data);
void usart_transmit(uint8_t data);
// void frequency_conversion(uint16_t millisecond_counter);

#endif