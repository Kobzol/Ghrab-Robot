/*
 * sonar.cpp
 *
 */

#include "../headers/sonar.h"

#define VZDALENOST_PARAMETR 100

void sonar_init()
{
	ON(TRIGGER_DDR, TRIGGER);
}
int* sonary_zmer()
{
	// zapnutí a vypnutí triggeru - sonary zaènou mìøit
	ON(TRIGGER_PORT, TRIGGER);
	delay(1);
	OFF(TRIGGER_PORT, TRIGGER);
       
	int* vzdalenosti = (int*) malloc(sizeof(int) * 3);
	
	for (int i = 0; i < 3; i++)
	{
		vzdalenosti[i] = 0;
	}

	// èeká se, dokud není napìtí na echu
	while (!PIN(SONAR_PREDNI_PIN, SONAR_PREDNI));
      
	// dokud je napìtí na echu, zvìtšuje se hodnota pocet
	while (PIN(SONAR_PREDNI_PIN, SONAR_PREDNI) || PIN(SONAR_PRAVY_PIN, SONAR_PRAVY) || PIN(SONAR_LEVY_PIN, SONAR_LEVY))
	{
		if (PIN(SONAR_PREDNI_PIN, SONAR_PREDNI))
		{
			vzdalenosti[0]++;
		}
		if (PIN(SONAR_PRAVY_PIN, SONAR_PRAVY))
		{
			vzdalenosti[1]++;
		}
		if (PIN(SONAR_LEVY_PIN, SONAR_LEVY))
		{
			vzdalenosti[2]++;
		}
	}
    
	return vzdalenosti;  
}
