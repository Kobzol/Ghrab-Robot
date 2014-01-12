/*
 * functions.h
 *
 */

#ifndef FUNKCE_H_
#define FUNKCE_H_

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

// PROCESOR
#define CLOCK_SPEED 8000000

// PRÁCE S PORTY
#define ON(a,b) (a |= (1<<b))
#define OFF(a,b) (a &=~ (1<<b))
#define PIN(a,b) (a & (1<<b))

// POMOCNÉ FUNKCE
void delay(unsigned int);
char* toString(unsigned int cislo, int *pole);

#endif