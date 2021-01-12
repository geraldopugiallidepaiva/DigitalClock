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

const uint8_t dias_mes_365[] = {31,28,31,30,31,30,31,31,30,31,30,31};
const uint8_t dias_mes_366[] = {31,29,31,30,31,30,31,31,30,31,30,31};

volatile uint8_t RTC_KeepAlarm;

void RTC_SetDateTime(uint8_t date, uint8_t month, uint16_t year, uint8_t weekday, uint8_t hour, uint8_t minute, uint8_t second);
void RTC_SetAlarm(uint8_t hour, uint8_t minute, uint8_t second, uint8_t keep);
void RTC_SetTimer(uint8_t hour, uint8_t minute, uint8_t second);
void RTC_StartChrono();
void RTC_StopChrono();
void RTC_CorrectTime();

#endif /* INC_INC_RTC_DIGITALCLOCK_H_ */
