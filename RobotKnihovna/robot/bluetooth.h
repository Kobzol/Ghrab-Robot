/*
 * bluetooth.h
 *
 * Created: 11.1.14 12:48:29
 *  Author: Jakub
 */ 

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <string.h>

#include "funkce.h"
#include "kompas.h"
#include "motor.h"
#include "sonar.h"

typedef unsigned char znak;
#define BT_ZADNY_ZNAK (255)
#define BT_TERMINACNI_ZNAK ('\0')
#define BT_ROZDELOVACI_ZNAK_ODPOVEDI (";")
#define BT_ROZDELOVACI_ZNAK_HODNOT ("-")

#define BT_VELIKOST_BUFFERU (50)
volatile znak bt_vstup[BT_VELIKOST_BUFFERU];

void bt_start(uint);
znak bt_prijmiZnak();
void bt_posliZnak(znak);
void bt_posliNeukoncenyRetezec(const char * retezec);
void bt_posliRetezec(const char *);
void bt_posliOdpoved(const char *, const char *);
void bt_posliVzdalenost(const char *, Vzdalenost);
void bt_posliStavMotoru();
void bt_vynulujBuffer();
void bt_provedPrikaz();

#endif /* BLUETOOTH_H_ */