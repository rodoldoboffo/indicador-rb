/*
 * ds3231.h
 *
 * Created: 20/09/2017 21:55:22
 *  Author: Rodolfo
 */ 

#ifndef DS3231_H_
#define DS3231_H_
#include <time.h>

#define DS3231_DEVICE_ADDRESS 0x68
#define DS3231_CLOCK PORTD6
#define DS3231_DATA PORTD7
#define DS3231_PORT PORTD
#define DS3231_PIN PIND
#define DS3231_DDR DDRD
#define DS3231_DATA_SET_MICROSEC_DELAY 100

#define DS3231_TIMEDATE_POINTER 0x00
#define DS3231_TEMPERATURE_POINTER 0x11
#define DS3231_MILLENIUM 2000

void initializeDS3231();
int ds3231readBytes(unsigned char deviceAddress, unsigned char wordAddress, unsigned char numBytes, unsigned char *buffer);
int ds3231writeBytes(unsigned char deviceAddress, unsigned char wordAddress, unsigned char numBytes, unsigned char *buffer);
void ds3231StartTransfer();
void ds3231StopTransfer();
void ds3231SetSerialDataDirection(unsigned char direction);
void ds3231SetSerialData(unsigned char state);
void ds3231SetSerialClock(unsigned char state);
void ds3231SendByte(unsigned char byte);
unsigned char ds3231ReceiveByte();
void ds3231SendBit(unsigned char bit);
unsigned char ds3231ReceiveBit();
void ds3231SendAck();
void ds3231SendNAck();
unsigned char ds3231ReceiveAck();

float ds3231GetTemperature();
int ds3231GetTimeDate(struct tm *t);
int ds3231SetTimeDate(struct tm *t);
#endif /* DS3231_H_ */