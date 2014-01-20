/*
 * sonar.cpp
 *
 */


#include "sonar.h"

void robot::sonar_init()
{
	ON(TRIGGER_DDR, TRIGGER);
}

robot::Vzdalenost robot::sonar_zmerVzdalenosti()
{
	// zapnutí a vypnutí triggeru - sonary zaènou mìøit
	ON(TRIGGER_PORT, TRIGGER);
	delay(1);
	OFF(TRIGGER_PORT, TRIGGER);
       
	Vzdalenost vzdalenost;

	// èeká se, dokud není napìtí na echu
	while (!PIN(SONAR_PREDNI_PIN, SONAR_PREDNI));
      
	// dokud je napìtí na echu, zvìtšuje se hodnota pocet
	while (PIN(SONAR_PREDNI_PIN, SONAR_PREDNI) || PIN(SONAR_PRAVY_PIN, SONAR_PRAVY) || PIN(SONAR_LEVY_PIN, SONAR_LEVY))
	{
		if (PIN(SONAR_PREDNI_PIN, SONAR_PREDNI))
		{
			vzdalenost.Vepredu++;
		}
		if (PIN(SONAR_LEVY_PIN, SONAR_LEVY))
		{
			vzdalenost.Vlevo++;
		}
		if (PIN(SONAR_PRAVY_PIN, SONAR_PRAVY))
		{
			vzdalenost.Vpravo++;
		}		
	}
    
	delay(1);
	
	return vzdalenost;  
}