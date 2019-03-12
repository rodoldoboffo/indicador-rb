/*
 * mystdlib.c
 *
 * Created: 30/04/2017 22:55:51
 *  Author: Rodolfo
 */ 

#include "indicator.h"
#include "mystdlib.h"
#include <util/delay.h>

unsigned char* ftoa(float v, unsigned char *str, unsigned int decimalPlaces) {
	unsigned char aux_str[MAX_STDLIB_STR_LEN], i=0, j=0, k=0;
	long intValue;
	if (v < 0) {
		str[k] = '-';
		v = v * -1.0;
		k++;
	}
	for (i = 0, intValue = (long)v, v = v - intValue; intValue != 0; i++) {
		aux_str[i] = (intValue % 10) + '0';
		intValue = intValue / 10;
	}
	if (i == 0) {
		aux_str[i] = '0';
		i++;
	}
	for (j = 0; j < i; j++, k++) {
		str[k] = aux_str[i-j-1];
	}
	str[k] = ',';
	k++;
	for (j = 0; j < decimalPlaces; j++, k++) {
		v = v * 10.0;
		str[k] = (int)v + '0';
		v = v - (int)v;
	}
	str[k] = '\0';
	return str;
}

unsigned char charArrayCmp(unsigned char *arr1, unsigned char *arr2, unsigned int offset, unsigned int count) {
	unsigned int i, end=offset+count;
	for (i=offset; i<end; i++) {
		if (arr1[i] != arr2[i]) return 0;
	}
	return 1;
}
