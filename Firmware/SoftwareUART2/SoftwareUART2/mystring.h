/*
 * mystring.h
 *
 * Created: 16/06/2017 13:17:02
 *  Author: Rodolfo
 */ 


#ifndef MYSTRING_H_
#define MYSTRING_H_

unsigned char stringStartsWith(const unsigned char* str, const unsigned char* prefix);
unsigned char replace(unsigned char* str, unsigned char old, unsigned char new);

#endif /* MYSTRING_H_ */