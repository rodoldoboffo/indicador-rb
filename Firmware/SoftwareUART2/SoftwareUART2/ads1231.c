/*
 * ads1231.c
 *
 * Created: 09/06/2017 07:15:43
 *  Author: Rodolfo
 */ 

#include "indicator.h"
#include "ads1231.h"
#include <avr/io.h>
#include <util/delay.h>

void adcInitialize(unsigned char speed) {
	DDRC |= (1<<ADC_SPEED_PIN) | (1<<ADC_PDWN_PIN) | (1<<ADC_SCLK_PIN);
	DDRC &= ~(1<<ADC_DOUT_PIN);
	PORTC |= (1<<ADC_DOUT_PIN) | (1<<ADC_PDWN_PIN);
	PORTC &= ~(1<<ADC_SCLK_PIN);
	if (speed)
		PORTC |= (1<<ADC_SPEED_PIN);
}

long int adcFetchData() {
	unsigned char i, j;
	long int d = 0UL, temp;
	for (j=0; j<DIGITAL_FILTER; ) {
		temp = 0UL;
		while ((PINC & (1<<ADC_DOUT_PIN)));
		for (i=0; i<24; i++) {
			PORTC |= (1<<ADC_SCLK_PIN);
			_delay_us(10);
			PORTC &= ~(1<<ADC_SCLK_PIN);
			temp <<= 1;
			if (PINC & (1<<ADC_DOUT_PIN)) temp |= 0x01;
			_delay_us(10);
		}
		PORTC |= (1<<ADC_SCLK_PIN);
		_delay_us(10);
		PORTC &= ~(1<<ADC_SCLK_PIN);
		_delay_us(10);
		if (temp & 0x800000) temp = temp | 0xFF000000;
		if (temp != -1L) { // desconsidera o ponto -1. parece algum problema do AD. preciso investigar melhor.
			d += temp;
			j++;
		}
	}
	d /= DIGITAL_FILTER;
	return d;
}