/*
 * bluetooth.h
 *
 * Created: 11.1.14 12:48:29
 *  Author: Jakub
 */ 


#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include "funkce.h"
#include "avr/io.h"
#include "avr/interrupt.h"

void bluetooth_init(uint);
znak receiveChar();
void writeChar(znak);

#endif /* BLUETOOTH_H_ */