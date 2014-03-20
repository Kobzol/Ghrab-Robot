/*
 * bluetooth.h
 *
 * Created: 11.1.14 12:48:29
 *  Author: Jakub
 */ 


#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include "avr/io.h"
#include "avr/interrupt.h"
#include "string.h"
#include "util/atomic.h"

#include "funkce.h"

#define BT_VELIKOST_BUFFERU (50)
volatile znak bt_vstup[BT_VELIKOST_BUFFERU] = { 0 };

void bt_start(uint);
znak bt_prijmiZnak();
void bt_posliZnak(znak);
void bt_posliRetezec(const char *);
void bt_vynulujBuffer();
void bt_provedPrikaz();

#endif /* BLUETOOTH_H_ */