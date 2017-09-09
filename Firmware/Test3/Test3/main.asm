;
; Test3.asm
;
; Created: 24/01/2017 08:13:36
; Author : Rodolfo
;


start:
	CALL USARTInit
loop:
	CALL USARTTransmit
    RJMP loop


USARTTransmit:
	LDS			r16, UCSR0A
	SBRS		r16, UDRE0
	RJMP		USARTTransmit
	LDI			r17, 'Y'
	STS			UDR0, r17
	RET

USARTInit:
	LDI			r17, 0
	LDI			r16, 103
	STS			UBRR0H, r17
	STS			UBRR0L, r16
	LDI			r16, (0|1<<RXEN0)|(1<<TXEN0)
	STS			UCSR0B, r16
	;frame format: 8bit data, 1bit stop
	LDI			r16, (0|3<<UCSZ00)
	STS			UCSR0C, r16
	RET
