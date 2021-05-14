#include "uart.h"
#include <stdio.h>


void usart_init(uint32_t ubrr){
	// Setting the register to 0 to start with
	UCSR0A=0x00;
	
	// Enabling the transmitter bit
	UCSR0B |= (1<<TXEN0);
	
	// Setting UART character size to 8-bits
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);
	
	// Formula to calculate UBRR value
	UBRR0=16000000/(16*ubrr)-1;
}

// need to understand why we use a for loop  :(
void usart_transmit(uint8_t data){
	for(uint8_t i=0; i<sizeof(data);i++){
		usart_transmit_byte(data);
	}
}

void usart_transmit_byte(uint8_t data){
	while ((UCSR0A & 0x20)==0){
		;
	}
	UDR0=data;
}

// find frequency and transmit via USART
/* void frequency_conversion(uint16_t millisecond_counter){
	uint8_t freq = 1000/(millisecond_counter);
	// char resultfreq[8];
	// sprintf(resultfreq, "%d", freq);
	//int i;
	uint8_t asciival[5], i;
	for(i = 0; i < 4; i++)
	{
		asciival[3-i] = ((freq)%10) + 48;
		freq = freq/10;
	}
	asciival[4] = 32;
	for(i = 0; i < sizeof(asciival); i++)
	{
		usart_transmit(asciival[i]);
	}
}
*/