/*
 * funkce.c
 *
 */ 

#include "funkce.h"

void bit_nastav(volatile uint8_t* reg, int pin)
{
	*reg |= (1 << pin);
}
void bit_vynuluj(volatile uint8_t* reg, int pin)
{
	*reg &= ~(1 << pin);
}
void bit_zmen(volatile uint8_t* reg, int pin, char nastav)
{
	if (nastav)
	{
		bit_nastav(reg, pin);
	}
	else bit_vynuluj(reg, pin);
}
void bit_prepni(volatile uint8_t* reg, int pin)
{
  *reg ^= (1 << pin);
}
char bit_vrat(volatile uint8_t* reg, int pin)
{
	return !!(*reg & (1 << pin));
}

void pockej(int ms)
{
	_delay_ms(ms);
}

void pockej_us(int us)
{
	const int limit = 760 / (F_CPU / 1000000UL);
	
	while (us > limit)
	{
		_delay_us(limit);
		us -= limit;
	}
	
	_delay_us(us);
}

void prevedNaRetezec(char *buffer, int cislo)
{
	itoa(cislo, buffer, 10);	
}