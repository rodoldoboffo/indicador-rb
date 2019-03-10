/*
 * mystdlib.h
 *
 * Created: 30/04/2017 22:55:07
 *  Author: Rodolfo
 */ 


#ifndef MYSTDLIB_H_
#define MYSTDLIB_H_

#define MAX_STDLIB_STR_LEN 10

unsigned char* ftoa(float v, unsigned char *str, unsigned int decimalPlaces);
unsigned char charArrayCmp(unsigned char *arr1, unsigned char *arr2, unsigned int offset, unsigned int count);

#endif /* MYSTDLIB_H_ */