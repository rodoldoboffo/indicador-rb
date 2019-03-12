/*
 * prc.c
 *
 * Created: 26/04/2017 16:45:26
 *  Author: Rodolfo
 */ 
//

#include "myutil.h"
#include "indicator.h"
#include "software_uart_ble.h"
#include "ads1231.h"
#include "ssr.h"

#include <string.h>
#include <util/delay.h>

const unsigned char GET_VAL_COMMAND[] = "getv";
const unsigned char BLE_AD_VAL_COMMAND[] = "adval=";
const unsigned char GET_STATE_COMMAND[] = "gets";
const unsigned char BLE_STATE_COMMAND[] = "stt=";
const unsigned char RELAY_ON_COMMAND[] = "rly1";
const unsigned char RELAY_OFF_COMMAND[] = "rly0";
const unsigned char READY[] = "ready\n";

long int globalADValue = 0L;

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
			globalADValue = getADValue();
			sendADValueToBle(globalADValue);
		}
		else if ((unsigned char *)strstr(commandBuffer, GET_STATE_COMMAND) == commandBuffer) {
			globalADValue = getADValue();
			unsigned char relayState = relayGetState();
			sendStateToBle(globalADValue, relayState);
		}
		else if ((unsigned char *)strstr(commandBuffer, RELAY_ON_COMMAND) == commandBuffer) {
			relayTurnOn();
			unsigned char relayState = relayGetState();
			sendStateToBle(globalADValue, relayState);
		}
		else if ((unsigned char *)strstr(commandBuffer, RELAY_OFF_COMMAND) == commandBuffer) {
			relayTurnOff();
			unsigned char relayState = relayGetState();
			sendStateToBle(globalADValue, relayState);
		}
	}
	resetBleBuffer();
}

long int getADValue() {
	unsigned char interruptState;
	interruptState = atomicBlockBleBegin();
	long int adValue = adcFetchFilteredData(1U);
	atomicBlockBleEnd(interruptState);
	return adValue;
}

void sendADValueToBle(long int adValue) {
	bleSerialPrint(";");
	bleSerialPrint(BLE_AD_VAL_COMMAND);
	bleSerialPrintLong(adValue);
	bleSerialPrint(";\n");
}

void sendStateToBle(long int adValue, unsigned char relay) {
	unsigned char buffer[12];
	bleSerialPrint(";");
	bleSerialPrint(BLE_STATE_COMMAND);
	convertToHex((unsigned char *)&adValue, sizeof(adValue), buffer);
	bleSerialPrint(buffer);
	convertToHex(&relay, sizeof(relay), buffer);
	bleSerialPrint(buffer);
	bleSerialPrint(";\n");
}
