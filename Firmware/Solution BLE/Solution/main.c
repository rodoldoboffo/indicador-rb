/*
 * Solution.c
 *
 * Created: 26/04/2017 11:04:09
 * Author : Rodolfo
 */ 


#include "nx4832t035.h"
#include "ds3231.h"
#include "software_uart.h"
#include "software_uart_ble.h"
#include "indicator.h"
#include <util/delay.h>
#include <time.h>

int main(void)
{
	initializeSystem();
	while (1)
	{
		processBLEMessages();
		if (sendADValue) {
			bleSendADValue();
		}
		//if (currentPage == MAIN_PAGE) {
			//updateMainNumbers();
			//updateTemperature();
			//if (overflowProtectionEnabled)
			//checkMachineOverflow();
			//_delay_ms(10);
		//}
		//if (currentPage == NEW_POINT_PAGE) {
			//updateNewPointDigitalValue();
			//_delay_ms(10);
		//}
		//softwareSerialPrint("Teste UART\n");
		//bleSerialPrint("AT+ADDR?");
		//_delay_ms(1000);
		//bleBufferReadAll(buffer);
		//softwareSerialPrint(buffer);
		//softwareSerialPrint("\n");
		//_delay_ms(100);
	}
}
