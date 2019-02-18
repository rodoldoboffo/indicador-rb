/*
 * prc.c
 *
 * Created: 26/04/2017 16:45:26
 *  Author: Rodolfo
 */ 
//

#include "indicator.h"
#include "software_uart_ble.h"
#include "ads1231.h"

#include <string.h>

const unsigned char BLE_AD_VAL_COMMAND[] = "adval=";
const unsigned char GET_VAL_COMMAND[] = "getv";
const unsigned char READY[] = "ready\n";

void initializeSystem() {
	initBleUARTSend();
	initBleUARTReceive();
	adcInitialize(0);
	
	//initializeRelay(!overflowProtectionMode);
	//_delay_ms(800);

	bleSerialPrint(READY);
}

void processBLEMessages() {
	unsigned char commandBuffer[36];
	while (serialBleFind(';') != -1) {
		bleBufferReadUntil(';', commandBuffer);
		if ((unsigned char *)strstr(commandBuffer, GET_VAL_COMMAND) == commandBuffer) {
			bleSendADValue();
		}
		//else if ((unsigned char *)strstr(commandBuffer, "rly1") == commandBuffer) {
			//relayTurnOn();
			//bleSerialPrint(";rlyon;");
		//}
		//else if ((unsigned char *)strstr(commandBuffer, "rly0") == commandBuffer) {
			//relayTurnOff();
			//bleSerialPrint(";rlyoff;");
		//}
	}
}

void bleSendADValue() {
	long int adValue = adcFetchData();
	bleSerialPrint(BLE_AD_VAL_COMMAND);
	bleSerialPrintLong(adValue);
	bleSerialPrint(";");
}
