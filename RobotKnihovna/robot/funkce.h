/*
 * functions.h
 *
 */

#ifndef FUNKCE_H_
#define FUNKCE_H_

#include <avr/io.h>

#ifndef RYCHLOST_PROCESORU
#warning Zadejte definici RYCHLOST_PROCESORU udavajici rychlost procesoru v Hz.
#define RYCHLOST_PROCESORU 8000000UL
#endif

// PRÁCE S PORTY
#define ZAPNI(a,b) (a |= (1<<b))
#define VYPNI(a,b) (a &=~ (1<<b))
#define ZKONTROLUJ(a,b) (a & (1<<b))

typedef uint16_t uint;
typedef unsigned long ulong;
typedef unsigned char znak;

// POMOCNÉ FUNKCE
void pockej(uint);

#endif