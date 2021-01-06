/*
 * lcd_shield.c
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

#include "lcd_shield.h"

void LCD_Clear(){
	HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
	HAL_Delay(100);
}
