/*
 * lcdkpd4stm32f401.h
 *
 *  Created on: 7 de out de 2020
 *      Author: lhalv
 */

#ifndef INC_LCDKPD4STM32F401_H_
#define INC_LCDKPD4STM32F401_H_

// includes 4ilo`s lcd library: https://github.com/4ilo/HD44780-Stm32HAL
#include "lcd.h"
#include "stm32f4xx_hal_adc.h"

#define BTN_RANGE 50

typedef enum {
	SELECT = 3820,
	LEFT = 2450,
	UP = 600,
	DOWN = 1540,
	RIGHT = 0,
	NONE = 4095
} Kpd_ButtonTypeDef;

uint16_t Analog_Read(ADC_HandleTypeDef *hadc);

Kpd_ButtonTypeDef Decode_Analog_Button(uint16_t value);

Kpd_ButtonTypeDef Debounce(ADC_HandleTypeDef *hadc, uint32_t counter_max);

Kpd_ButtonTypeDef Read_Button(ADC_HandleTypeDef *hadc, uint16_t counter_max);

#endif /* INC_LCDKPD4STM32F401_H_ */
