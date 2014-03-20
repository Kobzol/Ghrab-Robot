/*
 * bluetooth.cpp
 *
 */ 

#include "bluetooth.h"

void bluetooth_init(uint baud)
{
	// povolení interruptu
	sei();		
	
	// nastavení sériové linky
	uint16_t ubrr_value = ((RYCHLOST_PROCESORU) / (16UL * baud)) - 1;	
	
	// nastavení BAUDU
	UBRRL = ubrr_value;
	UBRRH = (ubrr_value >> 8);
	
	// asynchronous mode, 8 bitù, no parity, 1 stop bit 
	UCSRC = (1<<URSEL) | (3<<UCSZ0);
	UCSRB = (1<<RXEN) | (1<<TXEN);
}

znak receiveChar()
{
	if (UCSRA & (1<<RXC))
	{
		return UDR;				// vrátit pøijatý znak
	}	
	else return -1;		// nepøijat žádný znak
}

void writeChar(znak znakZpravy)
{
	while(!(UCSRA & (1<<UDRE)));	// poèkat, než bude buffer pøipraven
	
	UDR = znakZpravy;
}