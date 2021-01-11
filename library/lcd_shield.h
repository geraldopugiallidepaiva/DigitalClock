/*
 * lcd_shield.h
 *
 *  	Created on: January 5th 2021
 *
 *  	Universidade Federal de Minas Gerais
 *
 *  	Authors: 
 *          Eduardo Villani
 *          Geraldo Lucas Pugialli de Paiva
 *  	Version: 1.0.0
 *
 *  	Copyright 2021 - Under creative commons license
 *  	Attribution-NonCommercial-ShareAlike 4.0 International
 *  	(CC BY-NC-SA 4.0)
 *
 *  	This software is furnished "as is", without technical support, and with no
 *  	warranty, express or implied, as to its usefulness for any purpose.

 *
 *  	This API was developed as an assignment for the subject Embedded Systems
 *  	Programming at Universidade Federal de Minas Gerais
 *      Prof. Ricardo de Oliveira Duarte - Department of Electronic Engineering
 */

#ifndef INC_LCD_SHIELD_H_
#define INC_LCD_SHIELD_H_

#include "string.h"
#include "stdio.h"
#include "stm32f103xb.h"
#include "main.h"

// LCD display pins on LCD Shield (change accordingly)
#define LCD_RS_Pin     	GPIOA,GPIO_PIN_9
#define LCD_E_Pin      	GPIOC,GPIO_PIN_7
#define LCD_D4_Pin     	GPIOB,GPIO_PIN_5
#define LCD_D5_Pin     	GPIOB,GPIO_PIN_4
#define LCD_D6_Pin     	GPIOB,GPIO_PIN_10
#define LCD_D7_Pin   	GPIOA,GPIO_PIN_8
#define LCD_LED_Pin		GPIOB,GPIO_PIN_6

// Pushbutton ADC pins on LCD Shield (change accordingly)
#define BUTTON_Pin     GPIOA,GPIO_PIN_0

// LCD register select pin adresses
#define LCD_REG_COMMAND 	0
#define LCD_DATA_COMMAND 	1

// LCD commands
#define LCD_CLEAR 	0x01


// Pushbutton ADC values on LCD Shield
#define BUTTON_SEL_MAX      750
#define BUTTON_SEL_MIN      500
#define BUTTON_LEFT_MAX     500
#define BUTTON_LEFT_MIN     300
#define BUTTON_DOWN_MAX     300
#define BUTTON_DOWN_MIN     150
#define BUTTON_UP_MAX       150
#define BUTTON_UP_MIN       50
#define BUTTON_RIGHT_MAX    50
#define BUTTON_RIGHT_MIN    0

typedef enum{
	OFF = 0,
	ON = 1
} LED;

void LCD_SendNibble(uint8_t data);
void LCD_SendByte(uint8_t register_select, uint8_t data);

void LCD_Clear();

void LCD_Backlight(LED estado);



#endif /* INC_LCD_SHIELD_H_ */
