/*
 * multifunction_shield.h
 *
 *  	Created on: January 5th 2021
 *
 *  	Universidade Federal de Minas Gerais
 *
 *  	Authors: 
 *          Eduardo Villani
 *          Geraldo Lucas Pugialli de Paiva
 *  	Versão: 1.0.0
 *
 *  	Copyright 2021 - Under creative commons license
 *  	Attribution-NonCommercial-ShareAlike 4.0 International
 *  	(CC BY-NC-SA 4.0)
 *
 *  	This software is furnished "as is", without technical support, and with no
 *  	warranty, express or implied, as to its usefulness for any purpose.

 *
 *  	This API was developed as an assignment for the subject Embedded Systems Programming 
 *      at Universidade Federal de Minas Gerais
 *      Prof. Ricardo de Oliveira Duarte - Department of Electronic Engineering
 */

#ifndef INC_MULTIFUNCTION_SHIELD_H_
#define INC_MULTIFUNCTION_SHIELD_H_

// 7-segment dysplay digit selection addresses
#define DIGITO_1 0x8000
#define DIGITO_2 0x4000
#define DIGITO_3 0x2000
#define DIGITO_4 0x1000

// Numbers addresses
#define ALGARISMO_0 0x00FC
#define ALGARISMO_1 0x0060
#define ALGARISMO_2 0x00DA
#define ALGARISMO_3 0x00F2
#define ALGARISMO_4 0x0066
#define ALGARISMO_5 0x00B6
#define ALGARISMO_6 0x00BE
#define ALGARISMO_7 0x00E0
#define ALGARISMO_8 0x00FE
#define ALGARISMO_9 0x00F6

// Used letters addresses
#define LETRA_L 0x001C
#define LETRA_I 0x0060
#define LETRA_G 0x00BC
#define LETRA_d 0x007A
#define LETRA_E 0x009E
#define LETRA_S 0x00B6
#define LETRA_o 0x003A
#define LETRA_n 0x002A
#define LETRA_F 0x008E
#define LETRA_P 0x00CE

// Decimal dot address
#define PONTO 0x0001

// Empty character address
#define VAZIO 0x0000

void display_Init();

void buzzer_Init();

void pushbutton_Init();

void led_Init();

void display_ShowTime();

void display_ShowMenu();

void display_Clear();

void buzzer_On();

void buzzer_Off();

void led_ShowWeekday();

void led_ShowMenu();

#endif /* INC_MULTIFUNCTION_SHIELD_H_ */