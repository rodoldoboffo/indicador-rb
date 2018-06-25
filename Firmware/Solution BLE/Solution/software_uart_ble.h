/*
 * software_uart_ble.h
 *
 * Created: 17/05/2018 21:51:05
 *  Author: Rodolfo
 */ 


#ifndef SOFTWARE_UART_BLE_H_
#define SOFTWARE_UART_BLE_H_
#define BLE_BUFFER_SIZE 24
#include <time.h>

void resetBleBuffer();
void bleSendByte(unsigned char c);
void bleSendBit(unsigned char b);
void bleSerialPrint(const unsigned char *c);
void blePrintBuffer();
void bleSerialPrintInt(const int i);
void bleSerialPrintULong(const unsigned long l);
void bleSerialPrintFloat(const float f, unsigned char decimalPlaces);
void bleSerialPrintLong(const long l);
void initBleUARTSend();
void initBleUARTReceive();
void bleSerialPrintTm(const struct tm *t);
void disableBleInterupt();
void enableBleInterupt();
void bleBufferRead(unsigned int numBytes, unsigned char *buffer);
void bleBufferReadAll(unsigned char *buffer);
int serialBleFind(unsigned char c);
void bleBufferReadUntil(unsigned char stopChar, unsigned char *buffer);

#endif /* SOFTWARE_UART_BLE_H_ */