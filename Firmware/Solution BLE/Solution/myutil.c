/*
 * myutil.c
 *
 * Created: 10/03/2019 10:09:20
 *  Author: Rodolfo
 */ 

 void convertToHex(unsigned char * src, unsigned char size, unsigned char * dest) {
	unsigned char i;
	for (i = 0; i < size; i++) {
		unsigned char high = src[size-i-1] >> 4;
		if (high < 10) dest[2*i] = 0x30 + high;
		else dest[2*i] = 0x41 + high - 10;
		unsigned char low = src[size-i-1] & 0xF;
		if (low < 10) dest[2*i+1] = 0x30 + low;
		else dest[2*i+1] = 0x41 + low - 10;
	}
	dest[2*i] = 0;
 }