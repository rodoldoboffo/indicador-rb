/*
 * ssr.h
 *
 * Created: 16/08/2017 23:04:57
 *  Author: Rodolfo
 */ 


#ifndef SSR_H_
#define SSR_H_

#define SSR_PIN PORTB1

void initializeRelay(unsigned char onOff);
void relayTurnOn();
void relayTurnOff();
void relayOnOff(unsigned char onOff);

#endif /* SSR_H_ */