#include "adc.h"

void adc_init()
{
	// Using AVcc as our reference 
	ADMUX=(1<<REFS0);
	
	// Enable the register, and set the ADC prescaler to 64
	ADCSRA=0b10000110;
	
	// We set everything to 0 since this register isn't operated on
	ADCSRB=0x00;
}

uint16_t adc_read(uint8_t channel)
{
	//set the channel we wish to convert
	ADMUX |= channel;
	
	// start the conversion
	ADCSRA |= (1<<ADSC);
	
	// wait until conversion finishes
	while ((ADCSRA & (1<<ADIF))==0)
	{
		;
	}
	
	// store the data registers values in another variable
	uint16_t adc_count = (ADCL<<0)|(ADCH<<8);
	return adc_count;
}

uint16_t adc_convert(uint32_t adc_count)
{
	// convert in the range between 0 to 5 volts and with 10 steps (resolution)
	uint32_t millivolts = adc_count * (uint32_t)3300/1024;
	return (uint16_t)millivolts;
}