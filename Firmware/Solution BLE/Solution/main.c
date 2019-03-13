/*
 * Solution.c
 *
 * Created: 26/04/2017 11:04:09
 * Author : Rodolfo
 */ 


#include "indicator.h"
#include <util/delay.h>

int main(void)
{
	initializeSystem();
	while (1)
	{
		processBLEMessages();
		// Aparentemente esse tempo deve ser razoavelmente menor que o intervalo
		// de coleta do app android
		_delay_ms(5);
	}
}
