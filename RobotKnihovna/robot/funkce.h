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

#define F_CPU RYCHLOST_PROCESORU

#define __DELAY_BACKWARD_COMPATIBLE__

#include <util/delay.h>

#include <avr/io.h>
#include <stdlib.h>
#include <stdint.h>

void bit_nastav(volatile uint8_t* reg, int pin);
void bit_vynuluj(volatile uint8_t* reg, int pin);
void bit_zmen(volatile uint8_t* reg, int pin, char nastav);
void bit_prepni(volatile uint8_t* reg, int pin);
char bit_vrat(volatile uint8_t* reg, int pin);

void pockej(int ms);
void pockej_us(int us);

void prevedNaRetezec(char *buffer, int cislo);

typedef unsigned int uint;
typedef unsigned long ulong;

#define ZAPNI(port, pin) (bit_nastav(&port, pin))
#define VYPNI(port, pin) (bit_vynuluj(&port, pin))
#define ZKONTROLUJ(port, pin) (bit_vrat(&port, pin) != 0)
#define SMER_VYSTUP(port, pin) (bit_nastav(&port, pin))
#define SMER_VSTUP(port, pin) (bit_vynuluj(&port, pin))

#endif