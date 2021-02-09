/*
 * RTC_DigitalClock.h
 *
 *  Created on: 11/01/2020
 *      Author: Geraldo Lucas Pugialli de Paiva
 *
 */

#ifndef INC_RTC_DIGITALCLOCK_H_
#define INC_RTC_DIGITALCLOCK_H_

#include "main.h"

#include "lcd.h"
#include "lcdkpd4stm32f401.h"

extern RTC_HandleTypeDef hrtc;
extern Lcd_HandleTypeDef LCD;

// Weekdays labels (modify as needed)
// NOTE: The labels must contain 3 characters only
#define MONDAY_TEXT 	"Mon"
#define TUESDAY_TEXT 	"Tue"
#define WEDNESDAY_TEXT 	"Wed"
#define THURSDAY_TEXT 	"Thu"
#define FRIDAY_TEXT 	"Fri"
#define SATURDAY_TEXT 	"Sat"
#define SUNDAY_TEXT 	"Sun"

// Month labels (modify as needed)
// NOTE: The labels must contain 3 characters only
#define JANUARY_TEXT 	"Jan"
#define FEBRUARY_TEXT 	"Feb"
#define MARCH_TEXT 		"Mar"
#define APRIL_TEXT 		"Apr"
#define MAY_TEXT 		"May"
#define JUNE_TEXT 		"Jun"
#define JULY_TEXT 		"Jul"
#define AUGUST_TEXT 	"Aug"
#define SEPTEMBER_TEXT 	"Sep"
#define OCTOBER_TEXT 	"Oct"
#define NOVEMBER_TEXT 	"Nov"
#define DECEMBER_TEXT 	"Dec"

uint8_t FSM_State;
uint8_t FSM_NextState;

uint8_t StateChanged;
uint16_t ButtonIsPressed;

RTC_TimeTypeDef 	setTime;
RTC_DateTypeDef 	setDate;
RTC_AlarmTypeDef 	setAlarm;

uint8_t TimeCursor;
uint8_t DateCursor;
uint8_t AlarmCursor;

uint8_t TimeFormat;
uint8_t DateFormat;

Lcd_HandleTypeDef LCD;

typedef enum {
	DATE_WWW_DD_MM_YY,
	DATE_WWW_DD_MMM_YY,
	DATE_DD_MM_YY,
	DATE_DD_MMM_YY,
	DATE_WWW_MM_DD_YY,
	DATE_WWW_MMM_DD_YY,
	DATE_MM_DD_YY,
	DATE_MMM_DD_YY,
} DC_DateTypeDef;

typedef enum {
	TIME_HH_MM_SS,
	TIME_HH_MM,
} DC_TimeTypeDef;

DC_DateTypeDef DC_DateType;
DC_TimeTypeDef DC_TimeType;

void RTC_DC_Init();
void RTC_DC_SetDateTime(uint8_t date, uint8_t month, uint16_t year, uint8_t hour, uint8_t minute, uint8_t second);
void RTC_DC_SetAlarm(uint8_t hour, uint8_t minute, uint8_t second);
uint8_t RTC_DC_CheckDate(uint8_t date, uint8_t month, uint16_t year);
void RTC_DC_Display();

#endif /* INC_INC_RTC_DIGITALCLOCK_H_ */
