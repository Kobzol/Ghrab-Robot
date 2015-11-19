/*
 * sonar.c
 *
 */

#include "sonar.h"

void sonar_start()
{
	ZAPNI(TRIGGER_DDR, TRIGGER);
}

Vzdalenost sonar_zmerVzdalenosti()
{
	// zapnut� a vypnut� triggeru - sonary za�nou m��it
	ZAPNI(TRIGGER_PORT, TRIGGER);
	pockej(1);
	VYPNI(TRIGGER_PORT, TRIGGER);
       
	Vzdalenost vzdalenost = { 0, 0, 0 };

	// �ek� se, dokud nen� nap�t� na echu
	while (!ZKONTROLUJ(SONAR_PREDNI_PIN, SONAR_PREDNI));
      
	// dokud je nap�t� na echu, zv�t�uje se hodnota pocet
	while (ZKONTROLUJ(SONAR_PREDNI_PIN, SONAR_PREDNI) || ZKONTROLUJ(SONAR_PRAVY_PIN, SONAR_PRAVY) || ZKONTROLUJ(SONAR_LEVY_PIN, SONAR_LEVY))
	{
		if (ZKONTROLUJ(SONAR_LEVY_PIN, SONAR_LEVY))
		{
			vzdalenost.Vlevo++;
		}
		
		if (ZKONTROLUJ(SONAR_PREDNI_PIN, SONAR_PREDNI))
		{
			vzdalenost.Vepredu++;
		}
		
		if (ZKONTROLUJ(SONAR_PRAVY_PIN, SONAR_PRAVY))
		{
			vzdalenost.Vpravo++;
		}		
	}
    
	pockej(1);
	
	// 500 = 1 cm pro 1 MHz
	double faktor = (RYCHLOST_PROCESORU / 1000000UL) / 25.0;
	
	vzdalenost.Vepredu *= faktor;
	vzdalenost.Vlevo *= faktor;
	vzdalenost.Vpravo *= faktor;
	
	return vzdalenost;
}