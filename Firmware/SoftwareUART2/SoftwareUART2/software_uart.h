/*
 * software_uart.h
 *
 * Created: 08/06/2017 07:37:26
 *  Author: Rodolfo
 */ 



#ifndef SOFTWARE_UART_H_
#define SOFTWARE_UART_H_
#include <time.h>
#define SOFTWARE_SERIAL_BUFFER_SIZE 16

void resetSoftwareSerialBuffer();
void softwareSendByte(unsigned char c);
void softwareSendBit(unsigned char b);
void softwareSerialPrint(const unsigned char *c);
void softwareSerialPrintBuffer();
void softwareSerialPrintInt(const int i);
void softwareSerialPrintULong(const unsigned long l);
void softwareSerialPrintFloat(const float f, unsigned char decimalPlaces);
void softwareSerialPrintLong(const long l);
void initSoftwareUARTSend();
void initSoftwareUARTReceive();
void softwareSerialPrintTm(const struct tm *t);

#endif /* SOFTWARE_UART_H_ */