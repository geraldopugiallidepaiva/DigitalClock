/*
 * RTC_DigitalClock.h
 *
 *  Created on: 11/01/2020
 *      Author: Geraldo Lucas Pugialli de Paiva
 *
 */

#include "RTC_DigitalClock.h"

void RTC_SetDateTime(uint8_t date, uint8_t month, uint16_t year,
		uint8_t weekday, uint8_t hour, uint8_t minute, uint8_t second) {
	RTC_DateTypeDef auxDate;
	RTC_TimeTypeDef auxTime;

	while (HAL_RTC_GetState(&hrtc) != HAL_RTC_STATE_READY)
		;

	auxDate.Date = date;
	auxDate.Month = month;
	auxDate.Year = year % 100;
	auxDate.WeekDay = RTC_WEEKDAY_MONDAY;
	HAL_RTC_SetDate(&hrtc, &auxDate, RTC_FORMAT_BIN);

	auxTime.Hours = hour;
	auxTime.Minutes = minute;
	auxTime.Seconds = second;
	HAL_RTC_SetTime(&hrtc, &auxTime, RTC_FORMAT_BIN);

	return;
}

void RTC_SetAlarm(uint8_t hour, uint8_t minute, uint8_t second, uint8_t keep) {
	RTC_AlarmTypeDef auxAlarm;

	while (HAL_RTC_GetState(&hrtc) != HAL_RTC_STATE_READY)
		;

	auxAlarm.AlarmTime.Hours = hour;
	auxAlarm.AlarmTime.Minutes = minute;
	auxAlarm.AlarmTime.Seconds = second;
	HAL_RTC_SetAlarm_IT(&hrtc, &auxAlarm, RTC_FORMAT_BIN);

	RTC_KeepAlarm = keep;

	return;
}

void RTC_SetTimer(uint8_t hour, uint8_t minute, uint8_t second) {
	RTC_DateTypeDef auxDate;
	RTC_TimeTypeDef auxTime;
	RTC_AlarmTypeDef auxAlarm;

	while (HAL_RTC_GetState(&hrtc) != HAL_RTC_STATE_READY);

	HAL_RTC_GetDate(&hrtc, &auxDate, RTC_FORMAT_BIN);
	HAL_RTC_GetTime(&hrtc, &auxTime, RTC_FORMAT_BIN);

	uint16_t total_seconds_timer = second + (60 * minute) + (3600 * hour);

	uint8_t seconds_difference = 60 - auxTime.Seconds;
	uint8_t remainder = total_seconds_timer - seconds_difference;

	uint8_t minutes_difference = 60 - auxTime.Minutes;


	return;
}
void RTC_StartChrono();
void RTC_StopChrono();
void RTC_CorrectTime();
