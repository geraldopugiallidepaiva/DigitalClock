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

#include "gpio.h"
#include "string.h"
#include "stdio.h"
#include "stm32f103xb.h"
#include "main.h"

// LCD display pins on LCD Shield
#define LCD_RS_Port     GPIOA
#define LCD_RS_Pin      GPIO_PIN_9
#define LCD_E_Port      GPIOC
#define LCD_E_Pin       GPIO_PIN_7
#define LCD_D4_Port     GPIOB
#define LCD_D4_Pin      GPIO_PIN_5
#define LCD_D5_Port     GPIOB
#define LCD_D5_Pin      GPIO_PIN_4
#define LCD_D6_Port     GPIOB
#define LCD_D6_Pin      GPIO_PIN_10
#define LCD_D7_Port     GPIOA
#define LCD_D7_Pin      GPIO_PIN_8

// Pushbutton ADC pins on LCD Shield
#define BUTTON_Port     GPIOA
#define BUTTON_Pin      GPIO_PIN_0

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

void LCD_Write();
void LCD_SendCommand();
void LCD_SendData();

void LCD_Clear();



#endif /* INC_LCD_SHIELD_H_ */
