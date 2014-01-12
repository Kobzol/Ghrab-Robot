/*
 * bluetooth.h
 *
 * Created: 11.1.14 12:48:29
 *  Author: Jakub
 */ 


#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include "funkce.h"

#define RXD RXD
#define TXD TXD

void serial_init(uint16_t);
char receiveChar();
void writeChar(char);
void writeString(char*);
bool priselPrikaz();

#endif /* BLUETOOTH_H_ */