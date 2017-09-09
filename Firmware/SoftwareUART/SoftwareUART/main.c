/*
 * SoftwareUART.c
 *
 * Created: 16/05/2017 08:36:05
 * Author : Rodolfo
 */ 

 #define F_CPU 11059200

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void sendByte(unsigned char c);
void sendBit(unsigned char b);
void serialPrint(unsigned char *c);
void initSoftwareUARTSend();
void initSoftwareUARTReceive();
void testSoftwareUARTSend();
void testSoftwareUARTReceive();
void testTimer();

volatile unsigned char update = 0;
volatile unsigned char readChar = 0;
volatile unsigned char readBits = 0;

ISR(PCINT2_vect) {
	cli();
	unsigned char i;
	if (!(PIND & (1<<PORTD2))) {
		for (i=0, readChar=0; i<8; i++) {
			readChar >>= 1;
			TCCR1B |= (1 << CS10);
			while (!(TIFR1 & (1 << OCF1A)));
			TCCR1B &= ~(1 << CS10);
			if (PIND & (1<<PORTD2)) readChar |= 0x80;
			TIFR1 = (TIFR1 | (1 << OCF1A));
		}
		update = 1;
		//testSoftwareUARTSend();
	}
	sei();
}


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

int main(void)
{
	initSoftwareUARTSend();
	initSoftwareUARTReceive();
	while(1) {
		//if (update) {
			//cli();
			//sendByte(readChar);
			//update = 0;
			//sei();
		//}
		testSoftwareUARTSend();
		_delay_ms(500);
	}
}

void testTimer();

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

void testSoftwareUARTSend() {
	serialPrint("Pipoca na panela comeca a arrebentar\n");
}

void serialPrint(unsigned char *c) {
	unsigned char i;
	for (i=0; c[i] != 0; i++) {
		sendByte(c[i]);
	}
}

void sendByte(unsigned char c) {
	unsigned char i;
	sendBit(0);
	for (i = 0; i < 8; i++) {
		sendBit(c & 0x01);
		c >>= 1;
	}
	sendBit(1);
}

void sendBit(unsigned char b) {
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