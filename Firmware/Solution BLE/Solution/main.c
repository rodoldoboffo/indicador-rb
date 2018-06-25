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
		blePrintBuffer();
		bleSerialPrint("\n");
		_delay_ms(200);
	}
}
