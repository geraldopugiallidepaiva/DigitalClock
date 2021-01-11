/*
 * lcdkpd4stm32f401.c
 *
 *  Created on: 7 de out de 2020
 *      Author: lhalv
 */

#include "lcdkpd4stm32f401.h"

uint16_t Analog_Read(ADC_HandleTypeDef *hadc)
{
	  HAL_ADC_Start(hadc);
	  HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY);
	  return HAL_ADC_GetValue(hadc);
}

Kpd_ButtonTypeDef Decode_Analog_Button(uint16_t value)
{
	Kpd_ButtonTypeDef pressed_button;
	if (value < SELECT + BTN_RANGE && value > SELECT - BTN_RANGE)
	{
		pressed_button = SELECT;
	}
	else if (value < LEFT + BTN_RANGE && value > LEFT - BTN_RANGE)
	{
		pressed_button = LEFT;
	}
	else if (value < UP + BTN_RANGE && value > UP - BTN_RANGE)
	{
		pressed_button = UP;
	}
	else if (value < DOWN + BTN_RANGE && value > DOWN - BTN_RANGE)
	{
		pressed_button = DOWN;
	}
	else if (value < RIGHT + BTN_RANGE && value > RIGHT - BTN_RANGE)
	{
		pressed_button = RIGHT;
	}
	else
	{
		pressed_button = NONE;
	}
	return pressed_button;
}

Kpd_ButtonTypeDef Debounce(ADC_HandleTypeDef *hadc, uint32_t counter_max)
{
	Kpd_ButtonTypeDef new_value, old_value;
	new_value = Decode_Analog_Button(Analog_Read(hadc));
	old_value = new_value;

	for(uint32_t i = 0; i < counter_max; ++i)
	{
		new_value = Decode_Analog_Button(Analog_Read(hadc));
		if(new_value != old_value)
		{
			// If value changes, restart poll
			i = 0;
		}
	}
	// Value has hopefully stabilized by now
	return new_value;
}

Kpd_ButtonTypeDef Read_Button(ADC_HandleTypeDef *hadc, uint16_t counter_max)
{
	Kpd_ButtonTypeDef button = Debounce(hadc, counter_max);
	return button;
}
