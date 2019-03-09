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

long int adcFetchFilteredData(unsigned char digitalFilter) {
	long int d = 0L, temp;
	adcFetchData();
	for (unsigned char j=0; j<digitalFilter; j++) {
		temp = adcFetchData();
		d += temp;
	}
	d /= digitalFilter;
	return d;
}

long int adcFetchNthData(unsigned char n) {
	unsigned char i;
	long int d = 0L;
	for (i = 0; i < n; i++) {
		d = adcFetchData();
	}
	return d;
}

long int adcFetchData() {
	unsigned char i;
	long int d = 0L;
	while ((PINC & (1<<ADC_DOUT_PIN)));
	for (i=0; i<24; i++) {
		PORTC |= (1<<ADC_SCLK_PIN);
		_delay_us(1);
		PORTC &= ~(1<<ADC_SCLK_PIN);
		d <<= 1;
		if (PINC & (1<<ADC_DOUT_PIN)) d |= 0x01;
		_delay_us(1);
	}
	PORTC |= (1<<ADC_SCLK_PIN);
	_delay_us(1);
	PORTC &= ~(1<<ADC_SCLK_PIN);
	_delay_us(1);
	if (d & 0x800000) d = d | 0xFF000000;
	return d;
}