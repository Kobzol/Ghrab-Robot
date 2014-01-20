/*
 * functions.h
 *
 */

#ifndef FUNKCE_H_
#define FUNKCE_H_

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

namespace robot
{
	
#ifndef RYCHLOST_PROCESORU
#warning Zadejte definici RYCHLOST_PROCESORU udavajici rychlost procesoru v Hz.
#define RYCHLOST_PROCESORU 1000000UL
#endif

// PRÁCE S PORTY
#define ON(a,b) (a |= (1<<b))
#define OFF(a,b) (a &=~ (1<<b))
#define PIN(a,b) (a & (1<<b))

// DIODA
#define DIODA PB0
#define DIODA_PORT PORTB
#define DIODA_DDR DDRB

// POMOCNÉ FUNKCE
void dioda_init();
void delay(unsigned int);
char* toString(unsigned int cislo, int *pole);
void vyblikejCislo(unsigned long cislo);

}

#endif