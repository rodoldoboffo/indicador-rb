/*
 * indicator.h
 *
 * Created: 26/04/2017 11:05:53
 *  Author: Rodolfo
 */ 


#ifndef INDICATOR_H_
#define INDICATOR_H_

#define F_CPU 11059200UL
#define BAUDRATE 9600UL

void initializeSystem();

void processBLEMessages();
long int getADValue();
void sendADValueToBle(long int adValue);
void sendStateToBle(long int adValue, unsigned char relay);

#endif /* INDICATOR_H_ */