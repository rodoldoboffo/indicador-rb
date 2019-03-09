/*
 * ads1231.h
 *
 * Created: 09/06/2017 07:16:06
 *  Author: Rodolfo
 */ 


#ifndef ADS1231_H_
#define ADS1231_H_

#define DIGITAL_FILTER 1

#define ADC_SPEED_PIN PORTC0
#define ADC_PDWN_PIN PORTC1
#define ADC_SCLK_PIN PORTC2
#define ADC_DOUT_PIN PORTC3

void adcInitialize(unsigned char speed);
long int adcFetchData();
long int adcFetchNthData(unsigned char n);
long int adcFetchFilteredData(unsigned char digitalFilter);

#endif /* ADS1231_H_ */