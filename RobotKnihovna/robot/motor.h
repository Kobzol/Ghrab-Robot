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

#define MOTOR_LEVY_1 PD3
#define MOTOR_LEVY_1_PORT PORTD
#define MOTOR_LEVY_1_DDR DDRD
#define MOTOR_LEVY_2 PD2
#define MOTOR_LEVY_2_PORT PORTD
#define MOTOR_LEVY_2_DDR DDRD
#define MOTOR_PRAVY_1 PD4
#define MOTOR_PRAVY_1_PORT PORTD
#define MOTOR_PRAVY_1_DDR DDRD
#define MOTOR_PRAVY_2 PD5
#define MOTOR_PRAVY_2_PORT PORTD
#define MOTOR_PRAVY_2_DDR DDRD

#define MOTOR_CAS_MEZI_OTOCENIM 500

#define ODPOVED_MOTOR_STAV ("c")

void motor_start();
void motor_levy_vpred();
void motor_levy_vzad();
void motor_pravy_vpred();
void motor_pravy_vzad();
void motor_levy_stop();
void motor_pravy_stop();
void motor_jed_dopredu();
void motor_jed_dozadu();
void motor_zastav();
void motor_toc_doprava();
void motor_toc_doleva();
void motor_toc_uhel(uint cilovy_uhel);

#endif /* MOTOR_H_ */