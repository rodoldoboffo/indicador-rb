/*
 * serial.h
 *
 * Created: 26/04/2017 11:07:40
 *  Author: Rodolfo
 */ 


#ifndef SERIAL_H_
#define SERIAL_H_

#define INPUT_SERIAL_BUFFER_LEN 24

void _serialInitialize(unsigned char rcap2h, unsigned char rcap2l);
void serialInitialize(unsigned long baudRate);

void serialEcho(void);
unsigned char serialReadChar();
void serialPutChar(const unsigned char c);
void serialPrint(const unsigned char *str);
void serialClearInputBuffer();
void serialBufferRead(unsigned int numBytes, unsigned char *buffer);
void serialBufferReadAll(unsigned char *buffer);
int serialFind(unsigned char c);
void serialBufferReadUntil(unsigned char stopChar, unsigned char *buffer);
void printSerialState();

#endif /* SERIAL_H_ */