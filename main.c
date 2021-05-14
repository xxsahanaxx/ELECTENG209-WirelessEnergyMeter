/*
 * Lab06.c
 *
 * Created: 17/10/2019 8:59:47 AM
 * Author : ssri365
 */ 


#define F_CPU 16000000//crystal

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include "timer0.h"
#include "adc.h"
#include "uart.h"
#include "processing.h"
#include "interrupt.h"
#include "led.h"


volatile uint8_t timerON = 0;
volatile uint8_t timerCounter = 0;


//Interrupt Service Routines
ISR(INT0_vect){
	// Start timer
	TCNT0 = 0;
	timerON = 1;
}

ISR(INT1_vect)
{
	//STOP_TIMER0
	timerON = 0;
	timerCounter = TCNT0;
}

int main(void)
{
	// Initialising the UART, ADC, timer and interrupts
	usart_init(9600);
	adc_init();
	timer0_init();
	interrupt_init();
	
	// Inputs and outputs
	DDRC = 0x00;
	DDRD = 0x00;
	DDRB = 0xFF;

	// sets global interrupts to enable
	sei();
	
	while(timerON == 0);
	while(timerON == 1);
	//convert_to_ASCII(timerCounter);
	
	// 53.28 is the value that needs to be displayed
	double theta = 2 * 3.14 * (pow(10, -3) * timerCounter * 4); 
	//convert_to_ASCII(theta);
	
	// 0.597 (with an inductive load -- have to confirm that)
	double powerFactor = cos(theta) *1000;
	
	
	// clears interrupts
	cli();
	
	while(1)
	{
	//********SAMPLING********
	// Setting the initial channel to 3, the voltage channel
	uint8_t channel = 0;

	 
	// Arrays that store the samples of voltage and current
	uint16_t vSamples[64], iSamples[64], iRmsSamples[8], vRmsSamples[8];
	
	uint16_t count;
	uint64_t Vrms = 0;
	uint64_t Irms = 0;
	uint64_t Vpeak=0;
	
	uint8_t indexv = 0, indexc = 0;
	

	
	//for (int i=0; i<8; i++){
		
			for(indexv = 0, indexc = 0; indexc < 64; )
			{
				// voltage sampling
				if(channel == 0)
				{
					// read from the ADC
					count = adc_read(channel);
					
					// Add the converted value as one of the samples
					vSamples[indexv] = adc_convert(count);
					indexv++;
					
					// change the channel for interleaving the samples
					channel = 4;
				}
				
				// current sampling
				else if(channel == 4)
				{
					count = adc_read(channel);
					// we divide the isamples by the ratio and divide the entire thing by the shunt resistance = 0.69437 ohms
					iSamples[indexc] = (adc_convert(count)/1.18)/0.69437;
					indexc++;
					// Set channel back to one to obtain a voltage sample
					channel = 0;
				}
			}
			Vrms= calculate_rms(vSamples);
			//vRmsSamples[i]= Vrms;
		
			// wxy.z should be the format of display
			Irms = calculate_rms(iSamples);
			//iRmsSamples[i] = Irms;
	//}
	
	
	/*uint32_t sumVrms=0;
	uint32_t sumIrms=0;
	//averaging the values in the sample arrays
	for (int i=0; i<8; i++){
		sumVrms = sumVrms + vRmsSamples[i];
		sumIrms = sumIrms + iRmsSamples[i];
	}
	
	Vrms = sumVrms/8;
	Irms = sumVrms/8;
	*/
	Vpeak = Vrms*sqrt(2) * 1.18;
	
	

	
	
	
	
	//uint32_t Ipeak = Irms * sqrt(2);
	
	
	uint64_t apparentPower = (Vrms * Irms)/1000;
	uint64_t realPower =apparentPower * (powerFactor/1000);

	convert_to_ASCII(Vpeak,1);
	convert_to_ASCII(Irms,2);		
	convert_to_ASCII(realPower,3);
	convert_to_ASCII(powerFactor,4);
		
	_delay_ms(5000);
	}
}

