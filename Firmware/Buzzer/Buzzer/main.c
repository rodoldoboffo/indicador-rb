/*
 * Buzzer.c
 *
 * Created: 01/08/2017 22:19:01
 * Author : Rodolfo
 */ 
#define F_CPU 11059200UL

#include <avr/io.h>
#include <util/delay.h>

#define BUZZER_PIN PORTC4

void initializeBuzzer();

int main(void)
{
    /* Replace with your application code */
	initializeBuzzer();
    while (1) 
    {
		for (long i=0; i<20; i++) {
			PORTC |= (1<<BUZZER_PIN);
			_delay_us(2000.0);
			PORTC &= ~(1<<BUZZER_PIN);
			_delay_us(2000.0);
		}
		_delay_ms(500);
    }
}

void initializeBuzzer() {
	DDRC |= (1<<BUZZER_PIN);
}

