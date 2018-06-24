/*
 * Solution.c
 *
 * Created: 26/04/2017 11:04:09
 * Author : Rodolfo
 */ 


#include "nx4832t035.h"
#include "ds3231.h"
#include "software_uart.h"
#include "indicator.h"
#include <util/delay.h>
#include <time.h>
//
//int main() {
	//float temp;
	//struct tm t;
	//ds3231initialize();
	//initSoftwareUARTSend();
	//while (1) {
		//temp = ds3231GetTemperature();
		//softwareSerialPrintFloat(temp, 2);
		//softwareSerialPrint("\n");
		//ds3231GetTimeDate(&t);
		//softwareSerialPrintTm(&t);
		//softwareSerialPrint("\n");
		//_delay_ms(600);
	//}
	//return 0;
//}


int main(void)
{
	initializeSystem();
	while (1)
	{
		processDisplayMessages();
		if (currentPage == MAIN_PAGE) {
			updateMainNumbers();
			updateTemperature();
			if (overflowProtectionEnabled)
			checkMachineOverflow();
			_delay_ms(10);
		}
		if (currentPage == NEW_POINT_PAGE) {
			updateNewPointDigitalValue();
			_delay_ms(10);
		}
	}
}
