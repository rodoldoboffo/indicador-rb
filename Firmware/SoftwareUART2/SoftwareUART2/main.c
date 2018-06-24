/*
 * SoftwareUART2.c
 *
 * Created: 16/05/2018 20:02:18
 * Author : Rodolfo
 */ 

#include "indicator.h"
#include <avr/io.h>
#include "ads1231.h"
#include "software_uart_ble.h"
//#include "software_uart.h"
#include <util/delay.h>

int main(void)
{
	long int adData = 0;
	initBleUARTSend();
	initBleUARTReceive();
	resetBleBuffer();
	adcInitialize(0);
	initSoftwareUARTSend();
	initSoftwareUARTReceive();
    while (1) 
    {
		//blePrintBuffer();
		//resetBleBuffer();
		//softwareSerialPrintBuffer();
		//resetSoftwareSerialBuffer();
		//adData = adcFetchData();
		//bleSerialPrintLong(adData);
		softwareSerialPrint("Teste UART\n");
		bleSerialPrint("Teste BLE UART\n");
		_delay_ms(200);
    }
}

