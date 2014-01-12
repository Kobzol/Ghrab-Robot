/*
 * functions.cpp
 *
 */ 

#include "../headers/funkce.h"

void delay(unsigned int x)	// jak dlouho
{
	unsigned int i, u;
	for (i = 0; i < x; i++)
	{
		for (u = 0; u < 1000; u++);
	}
}

char* toString(unsigned int cislo, int *pole)
{
	snprintf((char*) pole, 10, "%d", cislo);
	
	return (char*) pole;
}