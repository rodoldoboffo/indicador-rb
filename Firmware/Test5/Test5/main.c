/*
 * Test5.c
 *
 * Created: 21/04/2017 20:56:03
 * Author : Rodolfo
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = (1<<PORTB5);
	
	while(1)
	{
		PORTB^=(1<<PORTB5);
		_delay_ms(500);
	}
}