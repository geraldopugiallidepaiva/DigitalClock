/*
 * RTC_DigitalClock.h
 *
 *  Created on: 11/01/2020
 *      Author: Geraldo Lucas Pugialli de Paiva
 *
 */

#ifndef INC_RTC_DIGITALCLOCK_H_
#define INC_RTC_DIGITALCLOCK_H_

#include "rtc.h"

#define MONDAY_TEXT 	"SEG"
#define TUESDAY_TEXT 	"TER"
#define WEDNESDAY_TEXT 	"QUA"
#define THURSDAY_TEXT 	"QUA"
#define FRIDAY_TEXT 	"SEX"
#define SATURDAY_TEXT 	"SAT"
#define SUNDAY_TEXT 	"DOM"

#define DATE_FORMAT		"DDMMYY"

#define TIME_FORMAT		"HHMMSS"

volatile uint8_t RTC_KeepAlarm;

void RTC_SetDateTime(uint8_t date, uint8_t month, uint16_t year, uint8_t weekday, uint8_t hour, uint8_t minute, uint8_t second);
void RTC_SetAlarm(uint8_t hour, uint8_t minute, uint8_t second, uint8_t keep);
void RTC_StartStopChrono();
void RTC_UpdateChrono();
void RTC_CorrectTime();

#endif /* INC_INC_RTC_DIGITALCLOCK_H_ */
