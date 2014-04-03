/*
 * kompas.c
 *
 * Created: 11.1.14 12:49:41
 *  Author: Jakub
 */ 

#include "kompas.h"

ulong kompas_zmerUhel()
{
	ulong uhel = 0;
	
	while (!ZKONTROLUJ(KOMPAS_PIN, KOMPAS));
	
	while (ZKONTROLUJ(KOMPAS_PIN, KOMPAS))
	{
		uhel++;
	}
	
	uhel = uhel / 105; // magická konstanta
		
	return uhel;
}

int kompas_srovnejSmery(uint prvni_smer, uint druhy_smer)
{
	return prvni_smer == druhy_smer;
}