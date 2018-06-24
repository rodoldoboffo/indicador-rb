/*
 * software_uart_ble.c
 *
 * Created: 17/05/2018 21:53:55
 *  Author: Rodolfo
 */ 

/*
 * software_uart_ble.c
 *
 * Created: 08/06/2017 07:35:15
 *  Author: Rodolfo
 */ 
 
#include "indicator.h"
#include "software_uart_ble.h"
#include "mystdlib.h"

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <time.h>

volatile unsigned char bleBuffer[BLE_BUFFER_SIZE];
volatile unsigned char bleBufferLen = 0;
//
//ISR(PCINT2_vect) {
	//unsigned char i, readChar=0, storedOCR0AValue = OCR0A;
	//PCMSK2 &= ~(1 << PCINT23);
	//if (!(PIND & (1<<PORTD7))) {
		//OCR0A = OCR0A / 2;
		//TCCR0B |= (1 << CS02);
		//while (!(TIFR0 & (1 << OCF0A)));
		//TCCR0B &= ~(1 << CS02);
		//OCR0A = storedOCR0AValue;
		//for (i=0; i<8; i++) {
			//readChar >>= 1;
			//TCCR0B |= (1 << CS02);
			//while (!(TIFR0 & (1 << OCF0A)));
			//TCCR0B &= ~(1 << CS02);
			//if (PIND & (1<<PORTD7)) readChar |= 0x80;
			//TIFR0 = (TIFR0 | (1 << OCF0A));
		//}
		//bleBuffer[bleBufferLen] = readChar;
		//bleBufferLen = (bleBufferLen+1+BLE_BUFFER_SIZE-1) % (BLE_BUFFER_SIZE-1);
	//}
	//PCMSK2 |= (1 << PCINT23);
//}

ISR(PCINT2_vect) {
	unsigned char i, readChar=0;
	PCMSK2 &= ~(1 << PCINT23);
	if (!(PIND & (1<<PORTD7))) {
		OCR1A = 576;
		TCCR1B |= (1 << CS10);
		while (!(TIFR1 & (1 << OCF1A)));
		TCCR1B &= ~(1 << CS10);
		TIFR1 = (TIFR1 | (1 << OCF1A));
		OCR1A = 1152;
		for (i=0; i<8; i++) {
			readChar >>= 1;
			TCCR1B |= (1 << CS10);
			while (!(TIFR1 & (1 << OCF1A)));
			TCCR1B &= ~(1 << CS10);
			if (PIND & (1<<PORTD7)) readChar |= 0x80;
			TIFR1 = (TIFR1 | (1 << OCF1A));
		}
		bleBuffer[bleBufferLen] = readChar;
		bleBufferLen = (bleBufferLen+1+BLE_BUFFER_SIZE-1) % (BLE_BUFFER_SIZE-1);
	}
	PCMSK2 |= (1 << PCINT23);
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

void initBleUARTSend() {
	DDRD |= (1<<PORTD6);
	TCCR1B |= (1 << WGM12);
	OCR1A = 1152;
}

//void initBleUARTReceive() {
	//resetBleBuffer();
	//DDRD &= ~(1<<DDD7);
	//PORTD &= ~(1<<PORTD7);
	//TCCR0B |= (1 << WGM01);
	//OCR0A = 18;
	//PCICR |= (1 << PCIE2);
	//PCMSK2 |= (1 << PCINT23);
	//sei();
//}

void initBleUARTReceive() {
	DDRD &= ~(1<<DDD7);
	PORTD &= ~(1<<PORTD7);
	TCCR1B |= (1 << WGM12);
	OCR1A = 1152;
	PCICR |= (1 << PCIE2);
	PCMSK2 |= (1 << PCINT23);
	sei();
}

void resetBleBuffer() {
	for (int i = 0; i < BLE_BUFFER_SIZE; i++) bleBuffer[i] = 0;
	bleBufferLen = 0;
}

void bleSerialPrint(const unsigned char *c) {
	unsigned char i;
	for (i=0; c[i] != 0; i++) {
		bleSendByte(c[i]);
	}
}

void blePrintBuffer() {
	unsigned char i;
	for (i=0; bleBuffer[i] != 0 && i < BLE_BUFFER_SIZE; i++) {
		bleSendByte(bleBuffer[i]);
	}
}

void bleSerialPrintInt(const int i) {
	unsigned char output[16];
	itoa(i, output, 10);
	return bleSerialPrint(output);
}

void bleSerialPrintLong(const long l) {
	unsigned char output[16];
	ltoa(l, output, 10);
	return bleSerialPrint(output);
}

void bleSerialPrintULong(const unsigned long l) {
	unsigned char output[16];
	ultoa(l, output, 10);
	return bleSerialPrint(output);
}

void bleSerialPrintFloat(const float f, unsigned char decimalPlaces) {
	unsigned char output[16];
	ftoa(f, output, decimalPlaces);
	return bleSerialPrint(output);
}

void bleSerialPrintTm(const struct tm *t) {
	bleSerialPrintULong(t->tm_year);
	bleSerialPrint("-");
	bleSerialPrintULong(t->tm_mon);
	bleSerialPrint("-");
	bleSerialPrintULong(t->tm_mday);
	bleSerialPrint(" ");
	bleSerialPrintULong(t->tm_hour);
	bleSerialPrint(":");
	bleSerialPrintULong(t->tm_min);
	bleSerialPrint(":");
	bleSerialPrintULong(t->tm_sec);
}

void bleSendByte(unsigned char c) {
	unsigned char i;
	bleSendBit(0);
	for (i = 0; i < 8; i++) {
		bleSendBit(c & 0x01);
		c >>= 1;
	}
	bleSendBit(1);
}

void bleSendBit(unsigned char b) {
	TCCR1B &= ~(1 << CS10);
	if (b)
		PORTD = PORTD | (1 << PORTD6);
	else
		PORTD = PORTD & ~(1 << PORTD6);
	TCCR1B |= (1 << CS10);
	while (!(TIFR1 & (1 << OCF1A)));
	TIFR1 = (TIFR1 | (1 << OCF1A));
	TCCR1B &= ~(1 << CS10);
	return;
}