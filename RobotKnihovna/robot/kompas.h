/*
 * kompas.h
 *
 * Created: 11.1.14 12:49:19
 *  Author: Jakub
 */ 


#ifndef KOMPAS_H_
#define KOMPAS_H_

#include "funkce.h"

#define KOMPAS PD6
#define KOMPAS_PIN PIND

ulong kompas_zmerUhel();
int kompas_srovnejSmery(uint prvni_smer, uint druhy_smer);

#endif /* KOMPAS_H_ */