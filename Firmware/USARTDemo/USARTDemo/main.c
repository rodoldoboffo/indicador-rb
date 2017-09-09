/*
 * USARTDemo.c
 *
 * Created: 04/01/2017 22:01:58
 * Author : Rodolfo
 */ 

 #define F_CPU 11059200UL

 #define USART_BAUDRATE 9600
 #define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#include <avr/io.h>
#include <util/delay.h>

void USARTInit();
void USARTTransmit(unsigned char data);

int main(void)
{
    /* Replace with your application code */
	USARTInit(BAUD_PRESCALE);
	DDRB = (1<<PORTB5);
	PORTB = 0x00;
    while (1)
    {
		PORTB ^= (1<<PORTB5);
		_delay_ms(200);
		PORTB ^= (1<<PORTB5);
		USARTTransmit('T');
		_delay_ms(1000);
    }
}

void USARTInit(unsigned int ubrr) {
	UBRR0H = (unsigned char) (ubrr >> 8);
	UBRR0L = (unsigned char) ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00)&(0<<USBS0);
}

void USARTTransmit(unsigned char data) {
	// UCSRA = USART Control and Status Register A
	// When UDRE is 1, transmit buffer (UDR) is ready to receive new data
	while ( !( UCSR0A & (1<<UDRE0)) );
	// Put data into buffer to send the data
	// UDR = USART I/O Data Register
	UDR0 = data;
}