/*
 * Bludiste.cpp
 *
 * Created: 12.1.14 13:38:55
 *  Author: Jakub a Míša
 */ 

#include <avr/io.h>
#include "headers/funkce.h"
#include "headers/motor.h"
#include "headers/sonar.h"
#include "headers/kompas.h"
#include "headers/bluetooth.h"

int main(void)
{
	motor_init();
	sonar_init();
	
	int* vzdalenosti = NULL;
	
	while (true)
	{
		vzdalenosti = sonary_zmer();
		
		
		
		free(vzdalenosti);
	}
}
