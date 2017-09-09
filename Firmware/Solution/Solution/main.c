/*
 * Solution.c
 *
 * Created: 26/04/2017 11:04:09
 * Author : Rodolfo
 */ 

#include "indicator.h"
#include "nx4832t035.h"
#include "least_square.h"
#include "software_uart.h"
#include <util/delay.h>

int main(void)
{
	initializeSystem();
	while (1)
	{
		processDisplayMessages();
		if (currentPage == MAIN_PAGE) {
			updateMainNumbers();
			if (overflowProtectionEnabled)
				checkMachineOverflow();
			_delay_ms(50);
		}
		if (currentPage == NEW_POINT_PAGE) {
			updateNewPointDigitalValue();
			_delay_ms(50);
		}
	}
}
