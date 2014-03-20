/*
 * motor.h
 *
 * Created: 11.1.14 12:39:48
 *  Author: Jakub
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include <avr/io.h>
#include <stdlib.h>

#include "funkce.h"
#include "kompas.h"

#define MOTOR1 PD3
#define MOTOR1_PORT PORTD
#define MOTOR1_DDR DDRD
#define MOTOR2 PD2
#define MOTOR2_PORT PORTD
#define MOTOR2_DDR DDRD
#define MOTOR3 PD4
#define MOTOR3_PORT PORTD
#define MOTOR3_DDR DDRD
#define MOTOR4 PD5
#define MOTOR4_PORT PORTD
#define MOTOR4_DDR DDRD

#define CAS_MEZI_OTOCENIM 500

void motor_init();
void levy_vpred();
void levy_vzad();
void pravy_vpred();
void pravy_vzad();
void levy_stop();
void pravy_stop();
void jed_dopredu();
void jed_dozadu();
void zastav();
void toc_doprava();
void toc_doleva();
void toc_uhel(uint cilovy_uhel);

#endif /* MOTOR_H_ */