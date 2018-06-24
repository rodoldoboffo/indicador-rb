/*
 * passive_buzer.c
 *
 * Created: 31/07/2017 23:02:18
 *  Author: Rodolfo
 */ 

 #include "indicator.h"
 #include "passive_buzzer.h"
 #include <avr/io.h>
 #include <util/delay.h>

 void initializeBuzzer() {
	 DDRC |= (1<<BUZZER_PIN);
 }

 void playLowBuzz(float seconds) {
	unsigned long stillPlaying = seconds * 600;
	while (stillPlaying > 0) {
		PORTC |= (1<<BUZZER_PIN);
		_delay_us(830.0);
		PORTC &= ~(1<<BUZZER_PIN);
		_delay_us(830.0);
		stillPlaying--;
	}
 }
 
 void playHighBuzz(float seconds) {
	 unsigned long stillPlaying = seconds * 2000;
	 while (stillPlaying > 0) {
		 PORTC |= (1<<BUZZER_PIN);
		 _delay_us(250.0);
		 PORTC &= ~(1<<BUZZER_PIN);
		 _delay_us(250.0);
		 stillPlaying--;
	 }
 }