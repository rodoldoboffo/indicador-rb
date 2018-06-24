/*
 * serial.c
 *
 * Created: 26/04/2017 11:10:30
 *  Author: Rodolfo
 */ 

 #include "indicator.h"
 #include "software_uart.h"
 #include "serial.h"
 #include <avr/io.h>
 #include <string.h>
 #include <avr/interrupt.h>

 volatile unsigned char inputBuffer[INPUT_SERIAL_BUFFER_LEN];
 volatile unsigned char inBufferStartIndex=0;
 volatile unsigned char inBufferEndIndex=0;

 ISR(USART_RX_vect)
 {
	 unsigned char readChar = serialReadChar();
	 inputBuffer[inBufferEndIndex] = readChar;
	 inBufferEndIndex = (inBufferEndIndex + 1)%INPUT_SERIAL_BUFFER_LEN;
 }

 void serialInitialize(unsigned long baudRate) {
	unsigned char i;
	unsigned int usartBaudRate = (F_CPU / (BAUDRATE * 16UL)) - 1;

	for (i=0; i<INPUT_SERIAL_BUFFER_LEN; i++)
		inputBuffer[i]=0;

	// UBRR = USART Baud Rate Register
	UBRR0H = (unsigned char) (usartBaudRate >> 8);
	UBRR0L = (unsigned char) usartBaudRate;
	// UCSRB = USART Control and Status Register B
	// RXEN -> Receiver Enabled, TXEN -> Transmitter Enabled
	// RXCIE -> Receive Complete Interrupt Enabled
	UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	// UCSRC = USART Control and Status Register C
	// Default Asynchronous USART, Parity disabled, 1 Stop bit
	// UCSZ -> 011 = 8 data bits
	UCSR0C = (3<<UCSZ00);
	enableGlobalInterrupt();
 }

 void serialPutChar(const unsigned char data) {
	 // UCSRA = USART Control and Status Register A
	 // When UDRE is 1, transmit buffer (UDR) is ready to receive new data
	 while ( !( UCSR0A & (1<<UDRE0)) );
	 // Put data into buffer to send the data
	 // UDR = USART I/O Data Register
	 UDR0 = data;
 }

 unsigned char serialReadChar() {
	// UCSRA = USART Control and Status Register A
	// RXC = USART Receive Complete bit
	while ( !( UCSR0A & (1<<RXC0)) );
	// UDR = USART I/O Data Register
	return (unsigned char)UDR0;
 }

 void serialEcho(void) {
	serialPutChar(serialReadChar());
 }

 void serialClearInputBuffer() {
	 disableGlobalInterrupt();
	 inBufferStartIndex = inBufferEndIndex = 0;
	 enableGlobalInterrupt();
 }

 void serialPrint(const unsigned char *str) {
	 unsigned int i = 0;
	 for (i=0; str[i] != '\0'; i++) {
		 serialPutChar(str[i]);
	 }
 }

 void serialBufferRead(unsigned int numBytes, unsigned char *buffer) {
	 disableGlobalInterrupt();
	 unsigned int i;
	 while (((inBufferEndIndex-inBufferStartIndex+INPUT_SERIAL_BUFFER_LEN)%INPUT_SERIAL_BUFFER_LEN) < numBytes);
	 for (i=0U; i<numBytes; i++) {
		 buffer[i] = inputBuffer[(inBufferStartIndex+i)%INPUT_SERIAL_BUFFER_LEN];
	 }
	 buffer[i] = 0;
	 inBufferStartIndex = (inBufferStartIndex + numBytes)%INPUT_SERIAL_BUFFER_LEN;
	 enableGlobalInterrupt();
 }

 void serialBufferReadAll(unsigned char *buffer) {
	 unsigned char bufferLen = (inBufferEndIndex-inBufferStartIndex+INPUT_SERIAL_BUFFER_LEN)%INPUT_SERIAL_BUFFER_LEN;
	 if (bufferLen > 0) {
		 serialBufferRead(bufferLen, buffer);
	 }
 }

 int serialFind(unsigned char c) {
	int i;
	unsigned char bufferLen = (inBufferEndIndex-inBufferStartIndex+INPUT_SERIAL_BUFFER_LEN)%INPUT_SERIAL_BUFFER_LEN;
	if (bufferLen > 0) {
		for (i=0U; i<bufferLen; i++) {
			if (inputBuffer[(inBufferStartIndex+i)%INPUT_SERIAL_BUFFER_LEN] == c)
				return i;
		}
	}
	return -1;
 }

 void serialBufferReadUntil(unsigned char stopChar, unsigned char *buffer) {
	unsigned char i = 0;
	while (i == 0)
		i = serialFind(stopChar) + 1;
	serialBufferRead(i, buffer);
	return;
 }

 void printSerialState() {
	 unsigned char i;
	 softwareSendByte('[');
	 for (i=0; i<INPUT_SERIAL_BUFFER_LEN; i++) {
		 softwareSendByte(inputBuffer[i]);
	 }
	 softwareSerialPrint("] ");
	 softwareSerialPrintInt(inBufferStartIndex);
	 softwareSerialPrint(" - ");
	 softwareSerialPrintInt(inBufferEndIndex);
	 softwareSerialPrint("\n");
 }