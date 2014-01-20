/*
 * kompas.h
 *
 * Created: 11.1.14 12:49:19
 *  Author: Jakub
 */ 


#ifndef KOMPAS_H_
#define KOMPAS_H_

#include "funkce.h"

namespace robot
{

#define KOMPAS PD6
#define KOMPAS_PIN PIND

unsigned long kompas_zmerUhel();
bool kompas_srovnejSmery(unsigned int prvni_smer, unsigned int druhy_smer);

}

#endif /* KOMPAS_H_ */