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

void delay_us(uint32_t delay) {
	delay *= 32;
	while (delay--);
}

void LCD_SendNibble(uint8_t data) {
	// Puts nibble into D4-D7 bits
	HAL_GPIO_WritePin(LCD_D4_Pin, data & 0x01);
	HAL_GPIO_WritePin(LCD_D5_Pin, (data >> 1) & 0x02);
	HAL_GPIO_WritePin(LCD_D6_Pin, (data >> 2) & 0x04);
	HAL_GPIO_WritePin(LCD_D7_Pin, (data >> 3) & 0x08);

	// Drives an EN pulse
	HAL_GPIO_WritePin(LCD_E_Pin, 1);
	//HAL_Delay(1);
	delay_us(100);
	HAL_GPIO_WritePin(LCD_E_Pin, 0);
	return;
}

void LCD_SendByte(uint8_t register_select, uint8_t data) {
	// Selects the corresponding LCD register
	HAL_GPIO_WritePin(LCD_RS_Pin, register_select & 0x01);

	// Drives EN low
	HAL_GPIO_WritePin(LCD_E_Pin, 0);

	// Sends the first nibble
	LCD_SendNibble((data >> 4) & 0x0F);

	// Sends the second nibble
	LCD_SendNibble(data & 0x0f);
	return;
}

void LCD_Clear() {
	HAL_Delay(200);
	LCD_SendByte(0,0x20);
	HAL_Delay(200);
	LCD_SendByte(0, 0x28);
	HAL_Delay(200);
	LCD_SendByte(0, 0x01);
	HAL_Delay(200);
	LCD_SendByte(0, 0x06);
	HAL_Delay(200);
	LCD_SendByte(0, 0x08);
	HAL_Delay(200);
	LCD_SendByte(0, 0x0F);
	HAL_Delay(2000);
	LCD_SendByte(0, 0x01);
	return;
}

void LCD_Backlight(LED estado) {
	if (estado == ON) {
		HAL_GPIO_WritePin(LCD_LED_Pin, 1);
	} else {
		if (estado == OFF) {
			HAL_GPIO_WritePin(LCD_LED_Pin, 0);
		}
	}
	return;
}

