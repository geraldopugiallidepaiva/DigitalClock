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

volatile uint8_t RTC_KeepAlarm;

uint16_t RTC_YearComplement;

uint8_t StateChanged;

typedef enum {
	DATE_WWW_DD_MM_YY,
	DATE_WWW_DD_MM_YYYY,
	DATE_WWW_DD_MMM_YY,
	DATE_WWW_DD_MMM_YYYY,
	DATE_DD_MM_YY,
	DATE_DD_MM_YYYY,
	DATE_DD_MMM_YY,
	DATE_DD_MMM_YYYY,
	DATE_WWW_MM_DD_YY,
	DATE_WWW_MM_DD_YYYY,
	DATE_WWW_MMM_DD_YY,
	DATE_WWW_MMM_DD_YYYY,
	DATE_MM_DD_YY,
	DATE_MM_DD_YYYY,
	DATE_MMM_DD_YY,
	DATE_MMM_DD_YYYY,
} DC_DateTypeDef;

typedef enum {
	TIME_HH_MM_SS,
	TIME_HH_MM,
} DC_TimeTypeDef;

uint8_t DC_DateType;
uint8_t DC_TimeType;

void RTC_DC_SetDateTime(uint8_t date, uint8_t month, uint16_t year, uint8_t hour, uint8_t minute, uint8_t second);
void RTC_DC_SetAlarm(uint8_t hour, uint8_t minute, uint8_t second, uint8_t keep);
void RTC_DC_Display(uint8_t state);
void RTC_DC_StartStopChrono();
void RTC_DC_UpdateChrono();
void RTC_DC_CorrectTime();

#endif /* INC_INC_RTC_DIGITALCLOCK_H_ */
