/*
 * mystdlib.h
 *
 * Created: 30/04/2017 22:55:07
 *  Author: Rodolfo
 */ 


#ifndef MYSTDLIB_H_
#define MYSTDLIB_H_

#define MAX_STDLIB_STR_LEN 10
//
//void uitoa(unsigned int v, unsigned char *str);
//void itoa(int v, unsigned char *str);
//void litoa(long int v, unsigned char *str);
//void ultoa(unsigned long v, unsigned char *str);
unsigned char* ftoa(float v, unsigned char *str, unsigned int decimalPlaces);

unsigned char charArrayCmp(unsigned char *arr1, unsigned char *arr2, unsigned int offset, unsigned int count);

void sleep(int ms);

#endif /* MYSTDLIB_H_ */