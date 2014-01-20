/*
 * sonar.h
 *
 * Created: 11.1.14 12:48:22
 *  Author: Jakub
 */ 



#ifndef SONAR_H_
#define SONAR_H_

#include "funkce.h"

namespace robot
{
	
#define TRIGGER PD7
#define TRIGGER_PORT PORTD
#define TRIGGER_DDR DDRD
#define SONAR_PREDNI PB0
#define SONAR_PREDNI_PORT PORTB
#define SONAR_PREDNI_PIN PINB
#define SONAR_LEVY PB1
#define SONAR_LEVY_PORT PORTB
#define SONAR_LEVY_PIN PINB
#define SONAR_PRAVY PB2
#define SONAR_PRAVY_PORT PORTB
#define SONAR_PRAVY_PIN PINB

typedef unsigned int sonar_tik;

struct Vzdalenost {
	sonar_tik Vepredu;
	sonar_tik Vlevo;
	sonar_tik Vpravo;
	Vzdalenost() : Vepredu(0), Vlevo(0), Vpravo(0) {}
};

void sonar_init();
Vzdalenost sonar_zmerVzdalenosti();

}

#endif /* SONAR_H_ */