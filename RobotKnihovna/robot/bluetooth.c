/*
 * bluetooth.cpp
 *
 */ 

#include "bluetooth.h"

void bt_start(uint baud)
{
	// nastavení sériové linky
	uint16_t ubrr_value = ((RYCHLOST_PROCESORU) / (16UL * baud)) - 1;	
	
	// nastavení BAUDU
	UBRRL = ubrr_value;
	UBRRH = (ubrr_value >> 8);
	
	// asynchronous mode, 8 bitů, no parity, 1 stop bit 
	UCSRC = (1<<URSEL) | (3<<UCSZ0);
	UCSRB = (1<<RXEN) | (1<<TXEN);
	
	// povolení interruptu
	sei();
	
	UCSRB |= (1 << RXCIE);	// povolení interruptu pro přijmutí dat sériové linky
}

znak bt_prijmiZnak()
{
	if (UCSRA & (1<<RXC))
	{
		return UDR;				// vrátit přijatý znak
	}	
	else return -1;				// nepřijat žádný znak
}

void bt_posliZnak(znak znakZpravy)
{
	while( !(ZKONTROLUJ(UCSRA, UDRE)) );	// počkat, než bude buffer připraven
	UDR = znakZpravy;						// odeslání znaku
}

void bt_posliRetezec(const char * retezec)
{
	while (*retezec != '\0')
	{
		bt_posliZnak(*retezec);
		
		retezec++;
	}
	
	bt_posliZnak(*retezec);
}

void bt_vynulujBuffer()
{
	memset((void *) bt_vstup, 0, sizeof(*bt_vstup) * BT_VELIKOST_BUFFERU);
}

void bt_provedPrikaz()
{
	if (strcmp((const char *) bt_vstup, "ahoj") == 0)
	{
		bt_posliRetezec("ahoj kamo");
	}
	
	bt_vynulujBuffer();
}

ISR (USART_RXC_vect)
{
	znak prijatyZnak;
	prijatyZnak = UDR ; // uložení přijmutého znaku

	if (prijatyZnak == '.')
	{
		bt_provedPrikaz();
		bt_vynulujBuffer();
	}
	else bt_vstup[strlen((const char *) bt_vstup)] = prijatyZnak;
}