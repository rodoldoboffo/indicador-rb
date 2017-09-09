/*
 * software_uart.c
 *
 * Created: 08/06/2017 07:35:15
 *  Author: Rodolfo
 */ 
 
#include "indicator.h"
#include "software_uart.h"
#include "mystdlib.h"

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile unsigned char update = 0;
volatile unsigned char readChar = 0;
volatile unsigned char readBits = 0;
//
//ISR(PCINT2_vect) {
	//cli();
	//unsigned char i;
	//if (!(PIND & (1<<PORTD2))) {
		//for (i=0, readChar=0; i<8; i++) {
			//readChar >>= 1;
			//TCCR1B |= (1 << CS10);
			//while (!(TIFR1 & (1 << OCF1A)));
			//TCCR1B &= ~(1 << CS10);
			//if (PIND & (1<<PORTD2)) readChar |= 0x80;
			//TIFR1 = (TIFR1 | (1 << OCF1A));
		//}
		//update = 1;
	//}
	//sei();
//}


//ISR(PCINT2_vect) {
	//if (!(PIND & (1<<PORTD2))) {
		//readChar = 0;
		//readBits = 0;
		//TCCR1B |= (1 << CS10);
	//}
	//_delay_ms(1);
//}
//
//ISR(TIMER1_COMPA_vect) {
	//TIFR1 = (TIFR1 | (1 << OCF1A));
	////readChar >>= 1;
	////if (PIND & (1<<PORTD2))	readChar |= 0x80;
	////if (++readBits >= 8) {
		////TCCR1B &= ~(1 << CS10);
		////update = 1;
	////}
	//TCCR1B &= ~(1 << CS10);
	//readChar = 'R';
	//update = 1;
//}
//
//int main(void)
//{
	//initSoftwareUARTSend();
	//initSoftwareUARTReceive();
	//while(1) {
		//if (update) {
			//cli();
			//sendByte(readChar);
			//update = 0;
			//sei();
		//}
		////testSoftwareUARTSend();
	//}
//}

void initSoftwareUARTSend() {
	DDRD |= (1<<PORTD3);
	TCCR1B |= (1 << WGM12);
	OCR1A = 1152;
}

void initSoftwareUARTReceive() {
	DDRD &= ~(1<<PORTD2);
	PORTD |= (1<<PORTD2);
	TCCR1B |= (1 << WGM12);
	OCR1A = 1152;
	PCICR |= (1 << PCIE2);
	PCMSK2 |= (1 << PCINT18);
	sei();
}

void softwareSerialPrint(const unsigned char *c) {
	unsigned char i;
	for (i=0; c[i] != 0; i++) {
		softwareSendByte(c[i]);
	}
}

void softwareSerialPrintInt(const int i) {
	unsigned char output[16];
	itoa(i, output, 10);
	return softwareSerialPrint(output);
}

void softwareSerialPrintLong(const long l) {
	unsigned char output[16];
	ltoa(l, output, 10);
	return softwareSerialPrint(output);
}

void softwareSerialPrintULong(const unsigned long l) {
	unsigned char output[16];
	ultoa(l, output, 10);
	return softwareSerialPrint(output);
}

void softwareSerialPrintFloat(const float f, unsigned char decimalPlaces) {
	unsigned char output[16];
	ftoa(f, output, decimalPlaces);
	return softwareSerialPrint(output);
}

void softwareSendByte(unsigned char c) {
	unsigned char i;
	softwareSendBit(0);
	for (i = 0; i < 8; i++) {
		softwareSendBit(c & 0x01);
		c >>= 1;
	}
	softwareSendBit(1);
}

void softwareSendBit(unsigned char b) {
	TCCR1B &= ~(1 << CS10);
	if (b)
		PORTD = PORTD | (1 << PORTD3);
	else
		PORTD = PORTD & ~(1 << PORTD3);
	TCCR1B |= (1 << CS10);
	while (!(TIFR1 & (1 << OCF1A)));
	TIFR1 = (TIFR1 | (1 << OCF1A));
	TCCR1B &= ~(1 << CS10);
	return;
}