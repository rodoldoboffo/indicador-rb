/*
 * passive_buzzer.h
 *
 * Created: 31/07/2017 23:01:46
 *  Author: Rodolfo
 */ 


#ifndef PASSIVE_BUZZER_H_
#define PASSIVE_BUZZER_H_

#define BUZZER_PIN PORTC4

void initializeBuzzer();
void playLowBuzz(float seconds);
void playHighBuzz(float seconds);

#endif /* PASSIVE_BUZZER_H_ */