;
; Tests2.asm
;
; Created: 21/12/2016 08:22:19
; Author : Rodolfo
;


; Replace with your application code
start:
    ldi r16, (0|1<<PORTC5)
	ldi r17, 0xFF
	out DDRC, r17
	out PORTC, r16
here:
    rjmp here
