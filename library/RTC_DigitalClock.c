/*
 * RTC_DigitalClock.h
 *
 *  Created on: 11/01/2020
 *      Author: Geraldo Lucas Pugialli de Paiva
 *
 */

#include "RTC_DigitalClock.h"

void RTC_DC_SetDateTime(uint8_t date, uint8_t month, uint16_t year,
		uint8_t hour, uint8_t minute, uint8_t second) {
	RTC_DateTypeDef auxDate;
	RTC_TimeTypeDef auxTime;

	auxDate.Date = date;
	auxDate.Month = month;
	auxDate.Year = year % 100;
	auxDate.WeekDay = RTC_WEEKDAY_MONDAY;
	HAL_RTC_SetDate(&hrtc, &auxDate, RTC_FORMAT_BIN);

	RTC_YearComplement = ((year / 100) * 100) % 10000;

	auxTime.Hours = hour;
	auxTime.Minutes = minute;
	auxTime.Seconds = second;
	HAL_RTC_SetTime(&hrtc, &auxTime, RTC_FORMAT_BIN);

	return;
}

void RTC_DC_SetAlarm(uint8_t hour, uint8_t minute, uint8_t second, uint8_t keep) {
	RTC_AlarmTypeDef auxAlarm;

	auxAlarm.AlarmTime.Hours = hour;
	auxAlarm.AlarmTime.Minutes = minute;
	auxAlarm.AlarmTime.Seconds = second;
	HAL_RTC_SetAlarm_IT(&hrtc, &auxAlarm, RTC_FORMAT_BIN);

	RTC_KeepAlarm = keep;

	return;
}

void RTC_DC_Display() {
	if (StateChanged != 1) {
		Lcd_clear(&LCD);
		StateChanged = 1;
	}
	switch (FSM_State) {
	// [ERROR State]
	default: {
		Lcd_cursor(&LCD, 0, 6);
		Lcd_string(&LCD, "Error");
		Lcd_cursor(&LCD, 1, 2);
		Lcd_string(&LCD, "Reset device");
		break;
	}
		// [State 0] Time and Date continuous display
	case 0: {
		RTC_DateTypeDef date;
		RTC_TimeTypeDef time;
		HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);

		char weekday[4];

		switch (date.WeekDay) {
		case RTC_WEEKDAY_SUNDAY: {
			strcpy(weekday, SUNDAY_TEXT);
			break;
		}
		case RTC_WEEKDAY_MONDAY: {
			strcpy(weekday, MONDAY_TEXT);
			break;
		}
		case RTC_WEEKDAY_TUESDAY: {
			strcpy(weekday, TUESDAY_TEXT);
			break;
		}
		case RTC_WEEKDAY_WEDNESDAY: {
			strcpy(weekday, WEDNESDAY_TEXT);
			break;
		}
		case RTC_WEEKDAY_THURSDAY: {
			strcpy(weekday, THURSDAY_TEXT);
			break;
		}
		case RTC_WEEKDAY_FRIDAY: {
			strcpy(weekday, FRIDAY_TEXT);
			break;
		}
		case RTC_WEEKDAY_SATURDAY: {
			strcpy(weekday, SATURDAY_TEXT);
			break;
		}
		}

		char monthLabel[4];

		switch (date.WeekDay) {
		case 1: {
			strcpy(monthLabel, JANUARY_TEXT);
			break;
		}
		case 2: {
			strcpy(monthLabel, FEBRUARY_TEXT);
			break;
		}
		case 3: {
			strcpy(monthLabel, MARCH_TEXT);
			break;
		}
		case 4: {
			strcpy(monthLabel, APRIL_TEXT);
			break;
		}
		case 5: {
			strcpy(monthLabel, MAY_TEXT);
			break;
		}
		case 6: {
			strcpy(monthLabel, JUNE_TEXT);
			break;
		}
		case 7: {
			strcpy(monthLabel, JULY_TEXT);
			break;
		}
		case 8: {
			strcpy(monthLabel, AUGUST_TEXT);
			break;
		}
		case 9: {
			strcpy(monthLabel, SEPTEMBER_TEXT);
			break;
		}
		case 10: {
			strcpy(monthLabel, OCTOBER_TEXT);
			break;
		}
		case 11: {
			strcpy(monthLabel, NOVEMBER_TEXT);
			break;
		}
		case 12: {
			strcpy(monthLabel, DECEMBER_TEXT);
			break;
		}
		}

		switch (DC_DateType) {
		case DATE_WWW_DD_MM_YY: {
			char textDate[16];
			sprintf(textDate, "%s %02d/%02d/%02d", weekday, date.Date,
					date.Month, date.Year);
			Lcd_cursor(&LCD, 1, 2);
			Lcd_string(&LCD, textDate);
			break;
		}
		case DATE_WWW_DD_MM_YYYY: {
			char textDate[16];
			sprintf(textDate, "%s %02d/%02d/%04d", weekday, date.Date,
					date.Month, RTC_YearComplement + date.Year);
			Lcd_cursor(&LCD, 1, 1);
			Lcd_string(&LCD, textDate);
			break;
		}
		case DATE_WWW_DD_MMM_YY: {
			char textDate[16];
			sprintf(textDate, "%s  %02d %s %02d", weekday, date.Date,
					monthLabel, date.Year);
			Lcd_cursor(&LCD, 1, 1);
			Lcd_string(&LCD, textDate);
			break;
		}
		case DATE_WWW_DD_MMM_YYYY: {
			char textDate[16];
			sprintf(textDate, "%s  %02d %s %04d", weekday, date.Date,
					monthLabel, RTC_YearComplement + date.Year);
			Lcd_cursor(&LCD, 1, 0);
			Lcd_string(&LCD, textDate);
			break;
		}
		case DATE_DD_MM_YY: {
			char textDate[16];
			sprintf(textDate, "%02d/%02d/%02d", date.Date, date.Month,
					date.Year);
			Lcd_cursor(&LCD, 1, 4);
			Lcd_string(&LCD, textDate);
			break;
		}
		case DATE_DD_MM_YYYY: {
			char textDate[16];
			sprintf(textDate, "%02d/%02d/%04d", date.Date, date.Month,
					RTC_YearComplement + date.Year);
			Lcd_cursor(&LCD, 1, 3);
			Lcd_string(&LCD, textDate);
			break;
		}
		case DATE_DD_MMM_YY: {
			char textDate[16];
			sprintf(textDate, "%02d %s %02d", date.Date, monthLabel, date.Year);
			Lcd_cursor(&LCD, 1, 4);
			Lcd_string(&LCD, textDate);
			break;
		}
		case DATE_DD_MMM_YYYY: {
			char textDate[16];
			sprintf(textDate, "%02d %s %04d", date.Date, monthLabel,
					RTC_YearComplement + date.Year);
			Lcd_cursor(&LCD, 1, 3);
			Lcd_string(&LCD, textDate);
			break;
		}
		case DATE_WWW_MM_DD_YY: {
			char textDate[16];
			sprintf(textDate, "%s %02d/%02d/%02d", weekday, date.Month,
					date.Date, date.Year);
			Lcd_cursor(&LCD, 1, 2);
			Lcd_string(&LCD, textDate);
			break;
		}
		case DATE_WWW_MM_DD_YYYY: {
			char textDate[16];
			sprintf(textDate, "%s %02d/%02d/%04d", weekday, date.Month,
					date.Date, RTC_YearComplement + date.Year);
			Lcd_cursor(&LCD, 1, 1);
			Lcd_string(&LCD, textDate);
			break;
		}
		case DATE_WWW_MMM_DD_YY: {
			char textDate[16];
			sprintf(textDate, "%s  %s %02d %02d", weekday, monthLabel,
					date.Date, date.Year);
			Lcd_cursor(&LCD, 1, 1);
			Lcd_string(&LCD, textDate);
			break;
		}
		case DATE_WWW_MMM_DD_YYYY: {
			char textDate[16];
			sprintf(textDate, "%s  %s %02d %04d", weekday, monthLabel,
					date.Date, RTC_YearComplement + date.Year);
			Lcd_cursor(&LCD, 1, 0);
			Lcd_string(&LCD, textDate);
			break;
		}
		case DATE_MM_DD_YY: {
			char textDate[16];
			sprintf(textDate, "%02d/%02d/%02d", date.Month, date.Date,
					date.Year);
			Lcd_cursor(&LCD, 1, 4);
			Lcd_string(&LCD, textDate);
			break;
		}
		case DATE_MM_DD_YYYY: {
			char textDate[16];
			sprintf(textDate, "%02d/%02d/%04d", date.Month, date.Date,
					RTC_YearComplement + date.Year);
			Lcd_cursor(&LCD, 1, 3);
			Lcd_string(&LCD, textDate);
			break;
		}
		case DATE_MMM_DD_YY: {
			char textDate[16];
			sprintf(textDate, "%s %02d %02d", monthLabel, date.Date, date.Year);
			Lcd_cursor(&LCD, 1, 4);
			Lcd_string(&LCD, textDate);
			break;
		}
		case DATE_MMM_DD_YYYY: {
			char textDate[16];
			sprintf(textDate, "%s %02d %04d", monthLabel, date.Date,
					RTC_YearComplement + date.Year);
			Lcd_cursor(&LCD, 1, 3);
			Lcd_string(&LCD, textDate);
			break;
		}
		}

		switch (DC_TimeType) {
		case TIME_HH_MM_SS: {
			char textTime[16];
			sprintf(textTime, "%02d:%02d:%02d", time.Hours, time.Minutes,
					time.Seconds);
			Lcd_cursor(&LCD, 0, 4);
			Lcd_string(&LCD, textTime);
			break;
		}
		case TIME_HH_MM: {
			char textTime[16];
			sprintf(textTime, "%02d:%02d", time.Hours, time.Minutes);
			Lcd_cursor(&LCD, 0, 5);
			Lcd_string(&LCD, textTime);
			break;
		}
		}
		uint16_t raw = Read_Button(&hadc1, 100);
		if (raw != NONE) {
			ButtonIsPressed = raw;
		} else {
			if (ButtonIsPressed == SELECT) {
				FSM_State = 1;
				ButtonIsPressed = NONE;
				StateChanged = 0;
			}
		}
		break;
	}
		// [State 1] Settings menu
	case 1: {
		Lcd_cursor(&LCD, 0, 0);
		Lcd_string(&LCD, "----- Menu -----");
		switch (FSM_NextState) {
		default: {
			break;
		}
		case 0: {
			Lcd_cursor(&LCD, 1, 0);
			Lcd_string(&LCD, "Clock Display");
			break;
		}
		case 2: {
			Lcd_cursor(&LCD, 1, 0);
			Lcd_string(&LCD, "Time Set");
			HAL_RTC_GetTime(&hrtc, &setTime, RTC_FORMAT_BIN);
			HAL_RTC_GetDate(&hrtc, &setDate, RTC_FORMAT_BIN);
			break;
		}
		case 3: {
			Lcd_cursor(&LCD, 1, 0);
			Lcd_string(&LCD, "Date Set");
			HAL_RTC_GetTime(&hrtc, &setTime, RTC_FORMAT_BIN);
			HAL_RTC_GetDate(&hrtc, &setDate, RTC_FORMAT_BIN);
			break;
		}
		case 4: {
			Lcd_cursor(&LCD, 1, 0);
			Lcd_string(&LCD, "Time Format");
			break;
		}
		case 5: {
			Lcd_cursor(&LCD, 1, 0);
			Lcd_string(&LCD, "Date Format");
			break;
		}
		}
		uint16_t raw = Read_Button(&hadc1, 1000);
		if (raw != NONE) {
			ButtonIsPressed = raw;
		} else {
			if (ButtonIsPressed == SELECT) {
				FSM_State = FSM_NextState;
				ButtonIsPressed = NONE;
				StateChanged = 0;
			}
			if (ButtonIsPressed == UP) {
				if (FSM_NextState == 0) {
					FSM_NextState = 2;
				} else {
					if (FSM_NextState == 5) {
						FSM_NextState = 0;
					} else {
						FSM_NextState++;
					}
				}
				ButtonIsPressed = NONE;
				StateChanged = 0;
				Lcd_cursor(&LCD, 1, 0);
				Lcd_string(&LCD, "                ");
				HAL_Delay(10);
			}
			if (ButtonIsPressed == DOWN) {
				if (FSM_NextState == 2) {
					FSM_NextState = 0;
				} else {
					if (FSM_NextState == 0) {
						FSM_NextState = 5;
					} else {
						FSM_NextState--;
					}
				}
				ButtonIsPressed = NONE;
				StateChanged = 0;
				Lcd_cursor(&LCD, 1, 0);
				Lcd_string(&LCD, "                ");
				HAL_Delay(10);
			}
		}
		break;
	}
		// [State 2] Time set
	case 2: {
		char textTime[16];
		sprintf(textTime, "%02d:%02d:%02d", setTime.Hours, setTime.Minutes,
				setTime.Seconds);
		Lcd_cursor(&LCD, 0, 4);
		Lcd_string(&LCD, textTime);
		switch (TimeCursor) {
		default: {
			break;
		}
		case 0: {
			Lcd_cursor(&LCD, 1, 4);
			char cursor[2];
			cursor[0] = 0b01011110;
			cursor[1] = 0;
			Lcd_string(&LCD, cursor);
			break;
		}
		case 1: {
			Lcd_cursor(&LCD, 1, 5);
			char cursor[2];
			cursor[0] = 0b01011110;
			cursor[1] = 0;
			Lcd_string(&LCD, cursor);
			break;
		}
		case 2: {
			Lcd_cursor(&LCD, 1, 7);
			char cursor[2];
			cursor[0] = 0b01011110;
			cursor[1] = 0;
			Lcd_string(&LCD, cursor);
			break;
		}
		case 3: {
			Lcd_cursor(&LCD, 1, 8);
			char cursor[2];
			cursor[0] = 0b01011110;
			cursor[1] = 0;
			Lcd_string(&LCD, cursor);
			break;
		}
		case 4: {
			Lcd_cursor(&LCD, 1, 10);
			char cursor[2];
			cursor[0] = 0b01011110;
			cursor[1] = 0;
			Lcd_string(&LCD, cursor);
			break;
		}
		case 5: {
			Lcd_cursor(&LCD, 1, 11);
			char cursor[2];
			cursor[0] = 0b01011110;
			cursor[1] = 0;
			Lcd_string(&LCD, cursor);
			break;
		}
		}

		uint16_t raw = Read_Button(&hadc1, 1000);
		if (raw != NONE) {
			ButtonIsPressed = raw;
		} else {
			if (ButtonIsPressed == SELECT) {
				FSM_State = 1;
				ButtonIsPressed = NONE;
				StateChanged = 0;
				RTC_DC_SetDateTime(setDate.Date, setDate.Month,
						setDate.Year + RTC_YearComplement, setTime.Hours,
						setTime.Minutes, setTime.Seconds);
			}
			if (ButtonIsPressed == RIGHT) {
				if (TimeCursor == 5) {
					TimeCursor = 0;
				} else {
					TimeCursor++;
				}
				ButtonIsPressed = NONE;
				Lcd_cursor(&LCD, 1, 0);
				Lcd_string(&LCD, "                ");
				HAL_Delay(10);
			}
			if (ButtonIsPressed == LEFT) {
				if (TimeCursor == 0) {
					TimeCursor = 5;
				} else {
					TimeCursor--;
				}
				ButtonIsPressed = NONE;
				Lcd_cursor(&LCD, 1, 0);
				Lcd_string(&LCD, "                ");
				HAL_Delay(10);
			}
			if (ButtonIsPressed == UP) {
				switch (TimeCursor) {
				default: {
					break;
				}
				case 0: {
					if (setTime.Hours >= 13) {
						setTime.Hours = setTime.Hours % 10;
					} else {
						setTime.Hours += 10;
					}
					break;
				}
				case 1: {
					if (setTime.Hours >= 23) {
						setTime.Hours = 00;
					} else {
						setTime.Hours += 1;
					}
					break;
				}
				case 2: {
					if (setTime.Minutes >= 50) {
						setTime.Minutes = setTime.Minutes % 10;
					} else {
						setTime.Minutes += 10;
					}
					break;
				}
				case 3: {
					if (setTime.Minutes >= 59) {
						setTime.Minutes = 00;
					} else {
						setTime.Minutes += 1;
					}
					break;
				}
				case 4: {
					if (setTime.Seconds >= 50) {
						setTime.Seconds = setTime.Seconds % 10;
					} else {
						setTime.Seconds += 10;
					}
					break;
				}
				case 5: {
					if (setTime.Seconds >= 59) {
						setTime.Seconds = 00;
					} else {
						setTime.Seconds += 1;
					}
					break;
				}
				}
				ButtonIsPressed = NONE;
				Lcd_cursor(&LCD, 1, 0);
				Lcd_string(&LCD, "                ");
				HAL_Delay(10);
			}
			if (ButtonIsPressed == DOWN) {
				switch (TimeCursor) {
				default: {
					break;
				}
				case 0: {
					if (setTime.Hours <= 3) {
						setTime.Hours = setTime.Hours % 10 + 20;
					} else {
						if (setTime.Hours > 3 && setTime.Hours <= 9) {
							setTime.Hours = setTime.Hours % 10 + 10;
						}
						else{
							setTime.Hours -= 10;
						}
					}
					break;
				}
				case 1: {
					if (setTime.Hours <= 0) {
						setTime.Hours = 23;
					} else {
						setTime.Hours -= 1;
					}
					break;
				}
				case 2: {
					if (setTime.Minutes <= 9) {
						setTime.Minutes = setTime.Minutes % 10 + 50;
					} else {
						setTime.Minutes -= 10;
					}
					break;
				}
				case 3: {
					if (setTime.Minutes <= 0) {
						setTime.Minutes = 59;
					} else {
						setTime.Minutes -= 1;
					}
					break;
				}
				case 4: {
					if (setTime.Seconds <= 9) {
						setTime.Seconds = setTime.Seconds % 10 + 50;
					} else {
						setTime.Seconds -= 10;
					}
					break;
				}
				case 5: {
					if (setTime.Seconds <= 0) {
						setTime.Seconds = 59;
					} else {
						setTime.Seconds -= 1;
					}
					break;
				}
				}
				ButtonIsPressed = NONE;
				Lcd_cursor(&LCD, 1, 0);
				Lcd_string(&LCD, "                ");
				HAL_Delay(10);
			}
		}
		break;
	}
		// [State 3] Date set
	case 3: {

		break;
	}
		// [State 4] Time format
	case 4: {

		break;
	}
		// [State 5] Date format
	case 5: {

		break;
	}
	}
}

void RTC_DC_StartStopChrono();
void RTC_DC_UpdateChrono();
void RTC_DC_CorrectTime();
