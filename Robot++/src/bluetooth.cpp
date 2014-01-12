/*
 * bluetooth.cpp
 *
 */ 

#include "../headers/bluetooth.h"

#define USART_MODE 2

void serial_init(uint16_t baud)
{
	// pøepoèet hodnoty
	uint16_t ubrr_value = CLOCK_SPEED / (USART_MODE*baud);	
	
	// nastavení BAUDU
	UBRRL = ubrr_value;
	UBRRH = (ubrr_value >>8);
	
	// asynchronous mode, 8 bitù, no parity, 1 stop bit 
	UCSRC = (1<<URSEL) | (3<<UCSZ0);
	UCSRB = (1<<RXEN) | (1<<TXEN);	
}

char receiveChar()
{
	if (UCSRA & (1<<RXC))
	{
		return UDR;		// vrátit pøijatý znak
	}	
	else return -1;		// nepøijat žádný znak
}

void writeChar(char znak)
{
	while(!(UCSRA & (1<<UDRE)));	// poèkat, než bude buffer pøipraven
	
	UDR = znak;
}

void writeString(char *retezec)
{
	while (true)
	{
		writeChar(*retezec++);
		if (*retezec == '\0')
		{
			writeChar('\0');
			break;
		}
	}
}

bool priselPrikaz()
{
	char znak = receiveChar();

	// nepøišel žádný pøíkaz
	if (znak == -1)
	{
		return false;
	}
	else if (znak == 'z')	
	{
		ON(PORTB, PB0);
	}
	else if (znak == 'v')
	{
		OFF(PORTB, PB0);
	}
	else if (znak == 'c')
	{
		int cislo = 567;
		int pole[10];
		writeString(toString(cislo, pole));
	}
	
	return true;
}