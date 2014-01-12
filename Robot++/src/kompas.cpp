/*
 * kompas.cpp
 *
 * Created: 11.1.14 12:49:41
 *  Author: Jakub
 */ 

#include "../headers/kompas.h"

unsigned long zmerUhel()
{
	unsigned long uhel = 0;
	
	while (!PIN(KOMPAS_PIN, KOMPAS));
	
	while (uhel += PIN(KOMPAS_PIN, KOMPAS))
	{
		//uhel++;
	}
	
	uhel = (uhel - 8000) / 100;
		
	return uhel;
}