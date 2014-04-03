/*
 * funkce.h
 *
 */

#ifndef FUNKCE_H_
#define FUNKCE_H_

#ifndef RYCHLOST_PROCESORU
	#warning Zadejte definici RYCHLOST_PROCESORU udavajici rychlost procesoru v Hz.
	#define RYCHLOST_PROCESORU 8000000UL
#endif

#include <avr/io.h>
#include <stdlib.h>

// PRÁCE S PORTY
#define ZAPNI(a,b) (a |= (1<<b))
#define VYPNI(a,b) (a &=~ (1<<b))
#define ZKONTROLUJ(a,b) (a & (1<<b))

typedef uint16_t uint;
typedef unsigned long ulong;

// POMOCNÉ FUNKCE
void pockej(uint);
void prevedNaRetezec(char *buffer, int cislo);

#endif