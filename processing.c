#include "processing.h"
#include "adc.h"
#include "uart.h"

uint16_t currentSample;

uint64_t calculate_rms(uint16_t *values)
{
	uint64_t sumsquares = 0;
	uint64_t rms = 0;
	//uint8_t arrsize = 0;
	for(int i = 0; i < 64; i++)
	{
		sumsquares += pow(values[i],2);
		//arrsize++;
	}
	sumsquares = sumsquares/64 ;
	rms = sqrt(sumsquares);
	return rms;
}

void convert_to_ASCII(uint64_t values, uint8_t flag)
{
	static uint8_t asciival[8];
	int i;
	asciival[1] = 61;//sets the second element to an equal sign
	asciival[7] = 10;//sets the last one to a new line
	
	switch(flag)
	{
		case 1: asciival[0] = 86;
				for(i = 2; i < 7; i++)
				{
					// Sets the digits such that the units place is stored at the end
					if (i==4)
					{
						asciival[8-i]=46;
						continue;
					}
					asciival[8-i] = ((values)%10) + 48;
					values = values/10;
				}
				break;
		case 2: asciival[0] = 73;
				for(i = 2; i < 7; i++)
				{
					// Sets the digits such that the units place is stored at the end
					if (i==3)
					{
						asciival[8-i]=46;
						continue;
					}
					asciival[8-i] = ((values)%10) + 48;
					values = values/10;
				}
				break;
		case 3: asciival[0] = 80;
				for(i = 2; i < 7; i++)
				{
					// Sets the digits such that the units place is stored at the end
					if (i==5)
					{
						asciival[8-i]=46;
						continue;
					}
					asciival[8-i] = ((values)%10) + 48;
					values = values/10;
				}
				break;
		case 4: asciival[0]	= 70;
				for(i = 2; i < 7; i++)
				{
					// Sets the digits such that the units place is stored at the end
					if (i==5)
					{
						asciival[8-i]=46;
						continue;
					}
					asciival[8-i] = ((values)%10) + 48;
					values = values/10;
				}
				break;
	}
	
	for(i = 0; i < 8; i++)
	{
		usart_transmit(asciival[i]);
	}
	
}

