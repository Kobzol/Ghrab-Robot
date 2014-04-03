/*
 * funkce.c
 *
 */ 

#include "funkce.h"
#include <stdint.h>

void pockej(uint delka)
{
	for (uint i = 0; i < delka; i++)
	{
		for (uint u = 0; u < 1000; u++);
	}
}

void prevedNaRetezec(char *buffer, int cislo)
{
	itoa(cislo, buffer, 10);	
}

/*void vyblikejCislo(ulong cislo)
{
	cislo += 100;
	
	ulong long delay_time = 120;
	ulong long pauza = 350;
	
	VYPNI(DIODA_PORT, DIODA);
	
	while (cislo >= 100)
	{
		cislo -= 100;
		ZAPNI(DIODA_PORT, DIODA);
		delay(delay_time);
		VYPNI(DIODA_PORT, DIODA);
		delay(delay_time);
	}
	
	delay(pauza);
	
	while (cislo >= 10)
	{
		cislo -= 10;
		ZAPNI(DIODA_PORT, DIODA);
		delay(delay_time);
		VYPNI(DIODA_PORT, DIODA);
		delay(delay_time);
	}
	
	delay(pauza);
	
	while (cislo >= 1)
	{
		cislo -= 1;
		ZAPNI(DIODA_PORT, DIODA);
		delay(delay_time);
		VYPNI(DIODA_PORT, DIODA);
		delay(delay_time);
	}
	
	delay(pauza);
}*/