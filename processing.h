#ifndef PROCESSING_H_

#define PROCESSING_H_

#include <avr/io.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t calculate_rms(uint16_t values[]);
void convert_to_ASCII(uint64_t values, uint8_t flag);
//void convert_to_ASCII(uint64_t values)
#endif