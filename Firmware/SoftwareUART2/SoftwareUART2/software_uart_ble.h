/*
 * software_uart_ble.h
 *
 * Created: 17/05/2018 21:51:05
 *  Author: Rodolfo
 */ 


#ifndef SOFTWARE_UART_BLE_H_
#define SOFTWARE_UART_BLE_H_
#define BLE_BUFFER_SIZE 16
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

#endif /* SOFTWARE_UART_BLE_H_ */