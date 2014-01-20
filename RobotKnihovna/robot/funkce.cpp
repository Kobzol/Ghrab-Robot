/*
 * functions.cpp
 *
 */ 

#include "funkce.h"

void robot::delay(unsigned int x)	// jak dlouho
{
	unsigned int i, u;
	for (i = 0; i < x; i++)
	{
		for (u = 0; u < 1000; u++);
	}
}

char* robot::toString(unsigned int cislo, int *pole)
{
	snprintf((char*) pole, 10, "%d", cislo);
	
	return (char*) pole;
}

void robot::vyblikejCislo(unsigned long cislo)
{
	cislo += 100;
	
	unsigned long long delay_time = 120;
	unsigned long long pauza = 350;
	
	OFF(DIODA_PORT, DIODA);
	
	while (cislo >= 100)
	{
		cislo -= 100;
		ON(DIODA_PORT, DIODA);
		delay(delay_time);
		OFF(DIODA_PORT, DIODA);
		delay(delay_time);
	}
	
	delay(pauza);
	
	while (cislo >= 10)
	{
		cislo -= 10;
		ON(DIODA_PORT, DIODA);
		delay(delay_time);
		OFF(DIODA_PORT, DIODA);
		delay(delay_time);
	}
	
	delay(pauza);
	
	/*while (cislo >= 1)
	{
		cislo -= 1;
		ON(DIODA_PORT, DIODA);
		delay(delay_time);
		OFF(DIODA_PORT, DIODA);
		delay(delay_time);
	}
	
	delay(pauza);*/
}