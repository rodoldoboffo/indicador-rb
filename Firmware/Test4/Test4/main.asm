;
; Test4.asm
;
; Created: 21/04/2017 20:41:49
; Author : Rodolfo
;

;.include "m328Pdef.inc"
; Replace with your application code
start:
	ldi		r16,		0xff
	out		ddrb,		r16

	ldi		r16,		0b00100000
	out		portb,		r16

loop:
    rjmp loop
