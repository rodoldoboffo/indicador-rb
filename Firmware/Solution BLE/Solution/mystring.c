/*
 * mystring.c
 *
 * Created: 16/06/2017 13:12:27
 *  Author: Rodolfo
 */ 

 #include "mystring.h"

 unsigned char stringStartsWith(const unsigned char* str, const unsigned char* prefix) {
	unsigned char i;
	for (i=0; prefix[i] != 0; i++) {
		if (str[i] != prefix[i]) return 0;
	}
	return 1;
 }

 unsigned char replace(unsigned char* str, unsigned char old, unsigned char new) {
	 unsigned char i;
	 for (i=0; str[i] != 0; i++)
	 if (str[i] == old) {
		 str[i] = new;
		 return 1;
	 }
	 return 0;
 }
 
  int find(unsigned char c, unsigned char inputBuffer) {
	  int i;
	  unsigned char bufferLen = (inBufferEndIndex-inBufferStartIndex+INPUT_SERIAL_BUFFER_LEN)%INPUT_SERIAL_BUFFER_LEN;
	  if (bufferLen > 0) {
		  for (i=0U; i<bufferLen; i++) {
			  if (inputBuffer[(inBufferStartIndex+i)%INPUT_SERIAL_BUFFER_LEN] == c)
			  return i;
		  }
	  }
	  return -1;
  }