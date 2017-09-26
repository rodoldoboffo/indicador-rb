/*
 * ds3231.c
 *
 * Created: 20/09/2017 21:54:25
 *  Author: Rodolfo
 */ 
 /*
 * clock.c
 *
 * Created: 13/09/2017 22:54:49
 * Author : Rodolfo
 */ 

#include "indicator.h"
#include "ds3231.h"
#include "software_uart.h"
#include <avr/io.h>
#include <util/delay.h>
#include <time.h>

void ds3231SetSerialDataDirection(unsigned char direction) {
	if (direction) {
		DS3231_DDR |= (1<<DS3231_DATA);
	}
	else {
		DS3231_DDR &= ~(1<<DS3231_DATA);
	}
}

void ds3231SetSerialData(unsigned char state) {
	if (state) {
		DS3231_PORT |= (1<<DS3231_DATA);
	}
	else {
		DS3231_PORT &= ~(1<<DS3231_DATA);
	}
}

void ds3231SetSerialClock(unsigned char state) {
	if (state) {
		DS3231_PORT |= (1<<DS3231_CLOCK);
	}
	else {
		DS3231_PORT &= ~(1<<DS3231_CLOCK);
	}
}

void initializeDS3231() {
	DS3231_DDR |= (1<<DS3231_CLOCK) | (1<<DS3231_DATA);
	DS3231_PORT |= (1<<DS3231_CLOCK) | (1<<DS3231_DATA);
	_delay_ms(100);
}

int ds3231readBytes(unsigned char deviceAddress, unsigned char wordAddress, unsigned char numBytes, unsigned char *buffer) {
	unsigned char b1 = 0;
	ds3231StartTransfer();
	deviceAddress = (deviceAddress << 1);
	ds3231SendByte(deviceAddress);
	b1 = ds3231ReceiveAck();
	if (b1 != 0) return -1;
	ds3231SendByte(wordAddress);
	b1 = ds3231ReceiveAck();
	if (b1 != 0) return -2;
	ds3231StartTransfer();
	deviceAddress |= 0x1;
	ds3231SendByte(deviceAddress);
	b1 = ds3231ReceiveAck();
	if (b1 != 0) return -3;
	for (unsigned char i=0; i<numBytes; i++) {
		buffer[i] = ds3231ReceiveByte();
		if (i==numBytes-1) {
			ds3231SendNAck();
		}
		else {
			ds3231SendAck();
		}
	}
	ds3231StopTransfer();
	return 0;
}

int ds3231writeBytes(unsigned char deviceAddress, unsigned char wordAddress, unsigned char numBytes, unsigned char *buffer) {
	unsigned char b1 = 0;
	ds3231StartTransfer();
	deviceAddress = (deviceAddress << 1);
	ds3231SendByte(deviceAddress);
	b1 = ds3231ReceiveAck();
	if (b1 != 0) return -1;
	ds3231SendByte(wordAddress);
	b1 = ds3231ReceiveAck();
	if (b1 != 0) return -2;
	for (unsigned char i=0; i<numBytes; i++) {
		ds3231SendByte(buffer[i]);
		b1 = ds3231ReceiveAck();
		if (b1 != 0) return -3;
	}
	ds3231StopTransfer();
	return 0;
}

void ds3231SendByte(unsigned char byte) {
	for (unsigned char i=0; i<8; i++) {
		ds3231SendBit(byte & 0x80);
		byte = byte << 1;
	}
}

unsigned char ds3231ReceiveByte() {
	unsigned char byte = 0;
	for (unsigned char i=0; i<8; i++) {
		byte = byte << 1;
		byte |= ds3231ReceiveBit();
	}
	return byte;
}

void ds3231SendBit(unsigned char bit) {
	ds3231SetSerialClock(0);
	_delay_us(DS3231_DATA_SET_MICROSEC_DELAY);
	ds3231SetSerialDataDirection(1);
	if (bit) {
		ds3231SetSerialData(1);
	}
	else {
		ds3231SetSerialData(0);
	}
	_delay_us(DS3231_DATA_SET_MICROSEC_DELAY);
	ds3231SetSerialClock(1);
	_delay_us(DS3231_DATA_SET_MICROSEC_DELAY);
}

unsigned char ds3231ReceiveBit() {
	unsigned char b = 0;
	ds3231SetSerialClock(0);
	_delay_us(DS3231_DATA_SET_MICROSEC_DELAY);
	ds3231SetSerialDataDirection(0);
	ds3231SetSerialData(0);
	_delay_us(DS3231_DATA_SET_MICROSEC_DELAY);
	ds3231SetSerialClock(1);
	_delay_us(DS3231_DATA_SET_MICROSEC_DELAY);
	if ((1<<DS3231_DATA) & DS3231_PIN) {
		b = 1;
	}
	return b;
}

void ds3231StartTransfer() {
	ds3231SetSerialDataDirection(1);
	ds3231SetSerialData(1);
	_delay_us(DS3231_DATA_SET_MICROSEC_DELAY);
	ds3231SetSerialData(0);
	_delay_us(DS3231_DATA_SET_MICROSEC_DELAY);
	ds3231SetSerialClock(0);
	_delay_us(DS3231_DATA_SET_MICROSEC_DELAY);
}

void ds3231StopTransfer() {
	ds3231SetSerialClock(0);
	ds3231SetSerialDataDirection(1);
	_delay_us(DS3231_DATA_SET_MICROSEC_DELAY);
	ds3231SetSerialData(0);
	_delay_us(DS3231_DATA_SET_MICROSEC_DELAY);
	ds3231SetSerialClock(1);
	_delay_us(DS3231_DATA_SET_MICROSEC_DELAY);
	ds3231SetSerialData(1);
	_delay_us(DS3231_DATA_SET_MICROSEC_DELAY);
}

unsigned char ds3231ReceiveAck() {
	return ds3231ReceiveBit();
}

void ds3231SendAck() {
	ds3231SendBit(0);
}
void ds3231SendNAck() {
	ds3231SendBit(1);
}

float ds3231GetTemperature() {
	float temp = 0.0;
	unsigned char buffer[2];
	int result = 0;
	result = ds3231readBytes(DS3231_DEVICE_ADDRESS, DS3231_TEMPERATURE_POINTER, 2, buffer);
	if (result != 0) return NAN;
	temp += (float)((char)buffer[0]) + ((float)(buffer[1]>>6))/4.0;
	return temp;
}

int ds3231GetTimeDate(struct tm *t) {
	unsigned char buffer[7];
	int result = 0;
	result = ds3231readBytes(DS3231_DEVICE_ADDRESS, DS3231_TIMEDATE_POINTER, 7, buffer);
	if (result != 0) return -1;
	t->tm_sec = (buffer[0] & 0x0F) + 10 * (buffer[0] >> 4);
	t->tm_min = (buffer[1] & 0x0F) + 10 * (buffer[1] >> 4);
	t->tm_hour = (buffer[2] & 0x0F) + 10 * ((buffer[2] >> 4) & 0x03);
	t->tm_wday = (buffer[3] & 0x07);
	t->tm_mday = (buffer[4] & 0x0F) + 10 * (buffer[4] >> 4);
	t->tm_mon = (buffer[5] & 0x0F) + 10 * ((buffer[5] >> 4) & 0x01);
	t->tm_year = (buffer[6] & 0x0F) + 10 * (buffer[6] >> 4) + DS3231_MILLENIUM;
	return 0;
}

int ds3231SetTimeDate(struct tm *t) {
	unsigned char buffer[7];
	int result = 0;
	buffer[0] = (t->tm_sec % 10) | ((t->tm_sec / 10) << 4);
	buffer[1] = (t->tm_min % 10) | ((t->tm_min / 10) << 4);
	buffer[2] = (t->tm_hour % 10) | ((t->tm_hour / 10) << 4);
	buffer[3] = (t->tm_wday);
	buffer[4] = (t->tm_mday % 10) | ((t->tm_mday / 10) << 4);
	buffer[5] = (t->tm_mon % 10) | ((t->tm_mon / 10) << 4);
	buffer[6] = ((t->tm_year % 100) % 10) | (((t->tm_year % 100) / 10) << 4);
	result = ds3231writeBytes(DS3231_DEVICE_ADDRESS, DS3231_TIMEDATE_POINTER, 7, buffer);
	if (result != 0) return -1;
	return 0;
}