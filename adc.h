#ifndef ADC_H_

#define ADC_H_

#include <avr/io.h>


void adc_init(void);
uint16_t adc_read(uint8_t channel);
uint16_t adc_convert(uint32_t adc_count);

#endif