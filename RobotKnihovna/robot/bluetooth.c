/*
 * bluetooth.cpp
 *
 */ 

#include "bluetooth.h"

void bluetooth_init(uint baud)
{
	// povolen� interruptu
	sei();		
	
	// nastaven� s�riov� linky
	uint16_t ubrr_value = ((RYCHLOST_PROCESORU) / (16UL * baud)) - 1;	
	
	// nastaven� BAUDU
	UBRRL = ubrr_value;
	UBRRH = (ubrr_value >> 8);
	
	// asynchronous mode, 8 bit�, no parity, 1 stop bit 
	UCSRC = (1<<URSEL) | (3<<UCSZ0);
	UCSRB = (1<<RXEN) | (1<<TXEN);
}

znak receiveChar()
{
	if (UCSRA & (1<<RXC))
	{
		return UDR;				// vr�tit p�ijat� znak
	}	
	else return -1;		// nep�ijat ��dn� znak
}

void writeChar(znak znakZpravy)
{
	while(!(UCSRA & (1<<UDRE)));	// po�kat, ne� bude buffer p�ipraven
	
	UDR = znakZpravy;
}