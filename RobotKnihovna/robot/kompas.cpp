/*
 * kompas.cpp
 *
 * Created: 11.1.14 12:49:41
 *  Author: Jakub
 */ 

#include "kompas.h"

unsigned long robot::kompas_zmerUhel()
{
	unsigned long uhel = 0;
	
	while (!PIN(KOMPAS_PIN, KOMPAS));
	
	while (PIN(KOMPAS_PIN, KOMPAS))
	{
		uhel++;
	}
	
	uhel = uhel / 22; // magická konstanta
		
	return uhel;
}

bool robot::kompas_srovnejSmery(unsigned int prvni_smer, unsigned int druhy_smer)
{
	return prvni_smer == druhy_smer;
}