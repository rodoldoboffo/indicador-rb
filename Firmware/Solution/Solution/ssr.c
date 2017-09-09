/*
 * ssr.c
 *
 * Created: 16/08/2017 23:01:42
 *  Author: Rodolfo
 */ 

 #include "ssr.h"
 #include <avr/io.h>

 void initializeRelay(unsigned char onOff) {
	DDRB |= (1<<SSR_PIN);
	relayOnOff(onOff);
 }

 void relayOnOff(unsigned char onOff) {
	if (onOff) {
		relayTurnOn();
	}
	else {
		relayTurnOff();
	}
 }

 void relayTurnOn() {
	PORTB |= (1<<SSR_PIN);
 }

 void relayTurnOff() {
	PORTB &= ~(1<<SSR_PIN);
 }