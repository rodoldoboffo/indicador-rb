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
#include "ssr.h"

#include <string.h>
#include <util/delay.h>

const unsigned char BLE_AD_VAL_COMMAND[] = "adval=";
const unsigned char GET_VAL_COMMAND[] = "getv";
const unsigned char RELAY_ON_COMMAND[] = "rly1";
const unsigned char RELAY_OFF_COMMAND[] = "rly0";
const unsigned char READY[] = "ready\n";

void initializeSystem() {
	initBleUARTSend();
	initBleUARTReceive();
	adcInitialize(1);
	initializeRelay(0);
	_delay_ms(800);
	bleSerialPrint(READY);
}

void processBLEMessages() {
	unsigned char commandBuffer[36];
	while (serialBleFind(';') != -1) {
		bleBufferReadUntil(';', commandBuffer);
		if ((unsigned char *)strstr(commandBuffer, GET_VAL_COMMAND) == commandBuffer) {
			bleSendADValue();
		}
		else if ((unsigned char *)strstr(commandBuffer, RELAY_ON_COMMAND) == commandBuffer) {
			relayTurnOn();
			bleSerialPrint(";rlyon;");
		}
		else if ((unsigned char *)strstr(commandBuffer, RELAY_OFF_COMMAND) == commandBuffer) {
			relayTurnOff();
			bleSerialPrint(";rlyoff;");
		}
	}
	resetBleBuffer();
}

void bleSendADValue() {
	long int adValue = adcFetchData();
	bleSerialPrint(BLE_AD_VAL_COMMAND);
	bleSerialPrintLong(adValue);
	bleSerialPrint(";");
}
