/*
 * RTC_DigitalClock.h
 *
 *  Created on: 11/01/2020
 *      Author: Geraldo Lucas Pugialli de Paiva
 *
 */

#include "RTC_DigitalClock.h"

void RTC_DC_Init() {
	ports[0] = GPIOB;
	ports[1] = GPIOB;
	ports[2] = GPIOB;
	ports[3] = GPIOA;

	pins[0] = GPIO_PIN_5;
	pins[1] = GPIO_PIN_4;
	pins[2] = GPIO_PIN_10;
	pins[3] = GPIO_PIN_8;

	LCD = Lcd_create(ports, pins, GPIOA, GPIO_PIN_9, GPIOC,
	GPIO_PIN_7, LCD_4_BIT_MODE);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1);
	blinkCounter = 0;
	Lcd_clear(&LCD);

	FSM_State = 1;
	DC_DateType = DATE_DD_MM_YY;
	DC_TimeType = TIME_HH_MM_SS;

	return;
}

void RTC_DC_SetDateTime(uint8_t date, uint8_t month, uint16_t year,
		uint8_t hour, uint8_t minute, uint8_t second) {
	RTC_DateTypeDef auxDate;
	RTC_TimeTypeDef auxTime;

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

void RTC_DC_SetAlarm(uint8_t hour, uint8_t minute, uint8_t second) {
	RTC_AlarmTypeDef auxAlarm;

	auxAlarm.AlarmTime.Hours = hour;
	auxAlarm.AlarmTime.Minutes = minute;
	auxAlarm.AlarmTime.Seconds = second;
	HAL_RTC_SetAlarm_IT(&hrtc, &auxAlarm, RTC_FORMAT_BIN);

	return;
}

void RTC_DC_AlarmInterrupt(void){
HAL_RTC_DeactivateAlarm(hrtc, RTC_ALARM_A);
FSM_State = 8;

/*Insert your own alarm event action*/
}

uint8_t RTC_DC_CheckDate(uint8_t date, uint8_t month, uint16_t year) {
	uint8_t status = 1;
	if (year % 4 == 0) {
		if (month == 2 && date > 29) {
			status = 0;
		}
	} else {
		if (month == 2 && date > 28) {
			status = 0;
		}
	}
	if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8
			|| month == 10 || month == 12) && date > 31) {
		status = 0;
	} else {
		if ((month == 4 || month == 6 || month == 9 || month == 11)
				&& date > 30) {
			status = 0;
		}
	}
	return status;
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

		switch (date.Month) {
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
		case DATE_WWW_DD_MMM_YY: {
			char textDate[16];
			sprintf(textDate, "%s  %02d %s %02d", weekday, date.Date,
					monthLabel, date.Year);
			Lcd_cursor(&LCD, 1, 1);
			Lcd_string(&LCD, &textDate[0]);
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
		case DATE_DD_MMM_YY: {
			char textDate[16];
			sprintf(textDate, "%02d %s %02d", date.Date, monthLabel, date.Year);
			Lcd_cursor(&LCD, 1, 4);
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
		case DATE_WWW_MMM_DD_YY: {
			char textDate[16];
			sprintf(textDate, "%s  %s %02d %02d", weekday, monthLabel,
					date.Date, date.Year);
			Lcd_cursor(&LCD, 1, 1);
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
		case DATE_MMM_DD_YY: {
			char textDate[16];
			sprintf(textDate, "%s %02d %02d", monthLabel, date.Date, date.Year);
			Lcd_cursor(&LCD, 1, 4);
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

		uint16_t raw = Read_Button(&hadc1, 10);
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
		case 6: {
			Lcd_cursor(&LCD, 1, 0);
			Lcd_string(&LCD, "Alarm Set");
			HAL_RTC_GetAlarm(&hrtc, &setAlarm, RTC_ALARM_A, RTC_FORMAT_BIN);
			break;
		}
		case 7: {
			Lcd_cursor(&LCD, 1, 0);
			Lcd_string(&LCD, "Alarm Clear");
			break;
		}
		}
		uint16_t raw = Read_Button(&hadc1, 10);
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
					if (FSM_NextState == 7) {
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
						FSM_NextState = 7;
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
		switch (AlarmCursor) {
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

		uint16_t raw = Read_Button(&hadc1, 10);
		if (raw != NONE) {
			ButtonIsPressed = raw;
		} else {
			if (ButtonIsPressed == SELECT) {
				FSM_State = 1;
				ButtonIsPressed = NONE;
				StateChanged = 0;
				RTC_DC_SetDateTime(setDate.Date, setDate.Month, setDate.Year,
						setTime.Hours, setTime.Minutes, setTime.Seconds);
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
					if (setTime.Hours > 13) {
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
						} else {
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
		char textDate[16];
		sprintf(textDate, "%02d/%02d/%02d", setDate.Date, setDate.Month,
				setDate.Year);
		Lcd_cursor(&LCD, 0, 4);
		Lcd_string(&LCD, textDate);
		switch (DateCursor) {
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

		uint16_t raw = Read_Button(&hadc1, 10);
		if (raw != NONE) {
			ButtonIsPressed = raw;
		} else {
			if (ButtonIsPressed == SELECT) {
				FSM_State = 1;
				ButtonIsPressed = NONE;
				StateChanged = 0;
				if (RTC_DC_CheckDate(setDate.Date, setDate.Month, setDate.Year)
						== 1) {
					RTC_DC_SetDateTime(setDate.Date, setDate.Month,
							setDate.Year, setTime.Hours, setTime.Minutes,
							setTime.Seconds);
				}
			}
			if (ButtonIsPressed == RIGHT) {
				if (DateCursor == 5) {
					DateCursor = 0;
				} else {
					DateCursor++;
				}
				ButtonIsPressed = NONE;
				Lcd_cursor(&LCD, 1, 0);
				Lcd_string(&LCD, "                ");
				HAL_Delay(10);
			}
			if (ButtonIsPressed == LEFT) {
				if (DateCursor == 0) {
					DateCursor = 5;
				} else {
					DateCursor--;
				}
				ButtonIsPressed = NONE;
				Lcd_cursor(&LCD, 1, 0);
				Lcd_string(&LCD, "                ");
				HAL_Delay(10);
			}
			if (ButtonIsPressed == UP) {
				switch (DateCursor) {
				default: {
					break;
				}
				case 0: {
					if (setDate.Date > 21 && setDate.Date != 30) {
						setDate.Date = setDate.Date % 10;
					} else {
						if (setDate.Date == 30) {
							setDate.Date = setDate.Date % 10 + 10;
						} else {
							setDate.Date += 10;
						}
					}
					break;
				}
				case 1: {
					if (setDate.Date >= 31) {
						setDate.Date = 1;
					} else {
						setDate.Date += 1;
					}
					break;
				}
				case 2: {
					if (setDate.Month <= 02) {
						setDate.Month += 10;
					} else {
						if (setDate.Month >= 11 && setDate.Month <= 12) {
							setDate.Month = setDate.Month % 10;
						}
					}
					break;
				}
				case 3: {
					if (setDate.Month >= 12) {
						setDate.Month = 01;
					} else {
						setDate.Month += 1;
					}
					break;
				}
				case 4: {
					if (setDate.Year >= 90) {
						setDate.Year = setDate.Year % 10;
					} else {
						setDate.Year += 10;
					}
					break;
				}
				case 5: {
					if (setDate.Year >= 99) {
						setDate.Year = 0;
					} else {
						setDate.Year += 1;
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
				switch (DateCursor) {
				default: {
					break;
				}
				case 0: {
					if (setDate.Date <= 9 && setDate.Date > 1) {
						setDate.Date = setDate.Date % 10 + 20;
					} else {
						if (setDate.Date <= 1) {
							setDate.Date = setDate.Date % 10 + 30;
						} else {
							if (setDate.Date == 10) {
								setDate.Date = 30;
							} else {
								setDate.Date -= 10;
							}
						}
					}
					break;
				}
				case 1: {
					if (setDate.Date <= 1) {
						setDate.Date = 31;
					} else {
						setDate.Date -= 1;
					}
					break;
				}
				case 2: {
					if (setDate.Month <= 02 && setDate.Month != 10) {
						setDate.Month = setDate.Month % 10 + 10;
					} else {
						if (setDate.Month != 10) {
							setDate.Month = setDate.Month % 10;
						}
					}
					break;
				}
				case 3: {
					if (setDate.Month <= 1) {
						setDate.Month = 12;
					} else {
						setDate.Month -= 1;
					}
					break;
				}
				case 4: {
					if (setDate.Year <= 10) {
						setDate.Year = setDate.Year % 10 + 90;
					} else {
						setDate.Year -= 10;
					}
					break;
				}
				case 5: {
					if (setDate.Year <= 0) {
						setDate.Year = 99;
					} else {
						setDate.Year -= 1;
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
		// [State 4] Time format
	case 4: {
		char textTime[16];
		switch (DC_TimeType) {
		case TIME_HH_MM_SS: {
			sprintf(textTime, "HH:MM:SS");
			Lcd_cursor(&LCD, 0, 4);
			Lcd_string(&LCD, textTime);
			Lcd_cursor(&LCD, 1, 6);
			Lcd_string(&LCD, " *.>");
			break;
		}
		case TIME_HH_MM: {
			sprintf(textTime, "HH:MM");
			Lcd_cursor(&LCD, 0, 5);
			Lcd_string(&LCD, textTime);
			Lcd_cursor(&LCD, 1, 6);
			Lcd_string(&LCD, "<.* ");
			break;
		}
		}

		uint16_t raw = Read_Button(&hadc1, 10);
		if (raw != NONE) {
			ButtonIsPressed = raw;
		} else {
			if (ButtonIsPressed == SELECT) {
				FSM_State = 1;
				ButtonIsPressed = NONE;
				StateChanged = 0;
			}
			if (ButtonIsPressed == RIGHT) {
				Lcd_clear(&LCD);
				DC_TimeType = TIME_HH_MM;
				ButtonIsPressed = NONE;
				HAL_Delay(10);
			}
			if (ButtonIsPressed == LEFT) {
				Lcd_clear(&LCD);
				DC_TimeType = TIME_HH_MM_SS;
				ButtonIsPressed = NONE;
				HAL_Delay(10);
			}
		}
		break;
	}
		// [State 5] Date format
	case 5: {
		char textDate[16];
		switch (DC_DateType) {
		case DATE_WWW_DD_MM_YY: {
			sprintf(textDate, "WWW DD/MM/YY");
			Lcd_cursor(&LCD, 0, 2);
			Lcd_string(&LCD, textDate);
			Lcd_cursor(&LCD, 1, 3);
			Lcd_string(&LCD, " *.......>");
			break;
		}
		case DATE_WWW_DD_MMM_YY: {
			sprintf(textDate, "WWW  DD MMM YY");
			Lcd_cursor(&LCD, 0, 1);
			Lcd_string(&LCD, textDate);
			Lcd_cursor(&LCD, 1, 3);
			Lcd_string(&LCD, "<.*......>");
			break;
		}
		case DATE_DD_MM_YY: {
			sprintf(textDate, "DD/MM/YY");
			Lcd_cursor(&LCD, 0, 4);
			Lcd_string(&LCD, textDate);
			Lcd_cursor(&LCD, 1, 3);
			Lcd_string(&LCD, "<..*.....>");
			break;
		}
		case DATE_DD_MMM_YY: {
			sprintf(textDate, "DD MMM YY");
			Lcd_cursor(&LCD, 0, 4);
			Lcd_string(&LCD, textDate);
			Lcd_cursor(&LCD, 1, 3);
			Lcd_string(&LCD, "<...*....>");
			break;
		}
		case DATE_WWW_MM_DD_YY: {
			sprintf(textDate, "WWW DD/MM/YY");
			Lcd_cursor(&LCD, 0, 2);
			Lcd_string(&LCD, textDate);
			Lcd_cursor(&LCD, 1, 3);
			Lcd_string(&LCD, "<....*...>");
			break;
		}
		case DATE_WWW_MMM_DD_YY: {
			sprintf(textDate, "WWW  MMM DD YY");
			Lcd_cursor(&LCD, 0, 1);
			Lcd_string(&LCD, textDate);
			Lcd_cursor(&LCD, 1, 3);
			Lcd_string(&LCD, "<.....*..>");
			break;
		}
		case DATE_MM_DD_YY: {
			sprintf(textDate, "MM/DD/YY");
			Lcd_cursor(&LCD, 0, 4);
			Lcd_string(&LCD, textDate);
			Lcd_cursor(&LCD, 1, 3);
			Lcd_string(&LCD, "<......*.>");
			break;
		}
		case DATE_MMM_DD_YY: {
			char textDate[16];
			sprintf(textDate, "MMM DD YY");
			Lcd_cursor(&LCD, 0, 4);
			Lcd_string(&LCD, textDate);
			Lcd_cursor(&LCD, 1, 3);
			Lcd_string(&LCD, "<.......* ");
			break;
		}
		}

		uint16_t raw = Read_Button(&hadc1, 10);
		if (raw != NONE) {
			ButtonIsPressed = raw;
		} else {
			if (ButtonIsPressed == SELECT) {
				FSM_State = 1;
				ButtonIsPressed = NONE;
				StateChanged = 0;
			}
			if (ButtonIsPressed == RIGHT) {
				Lcd_clear(&LCD);
				if (DC_DateType < DATE_MMM_DD_YY) {
					DC_DateType++;
				}
				ButtonIsPressed = NONE;
				HAL_Delay(10);
			}
			if (ButtonIsPressed == LEFT) {
				Lcd_clear(&LCD);
				if (DC_DateType > DATE_WWW_DD_MM_YY) {
					DC_DateType--;
				}
				ButtonIsPressed = NONE;
				HAL_Delay(10);
			}
		}
		break;
	}
		// [State 6] Set alarm
	case 6: {
		char textAlarm[16];
		sprintf(textAlarm, "%02d:%02d:%02d", setAlarm.AlarmTime.Hours,
				setAlarm.AlarmTime.Minutes, setAlarm.AlarmTime.Seconds);
		Lcd_cursor(&LCD, 0, 4);
		Lcd_string(&LCD, textAlarm);
		switch (AlarmCursor) {
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

		uint16_t raw = Read_Button(&hadc1, 10);
		if (raw != NONE) {
			ButtonIsPressed = raw;
		} else {
			if (ButtonIsPressed == SELECT) {
				FSM_State = 1;
				ButtonIsPressed = NONE;
				StateChanged = 0;
				RTC_DC_SetAlarm(setAlarm.AlarmTime.Hours,
						setAlarm.AlarmTime.Minutes, setAlarm.AlarmTime.Seconds);
			}
			if (ButtonIsPressed == RIGHT) {
				if (AlarmCursor == 5) {
					AlarmCursor = 0;
				} else {
					AlarmCursor++;
				}
				ButtonIsPressed = NONE;
				Lcd_cursor(&LCD, 1, 0);
				Lcd_string(&LCD, "                ");
				HAL_Delay(10);
			}
			if (ButtonIsPressed == LEFT) {
				if (AlarmCursor == 0) {
					AlarmCursor = 5;
				} else {
					AlarmCursor--;
				}
				ButtonIsPressed = NONE;
				Lcd_cursor(&LCD, 1, 0);
				Lcd_string(&LCD, "                ");
				HAL_Delay(10);
			}
			if (ButtonIsPressed == UP) {
				switch (AlarmCursor) {
				default: {
					break;
				}
				case 0: {
					if (setAlarm.AlarmTime.Hours > 13) {
						setAlarm.AlarmTime.Hours = setAlarm.AlarmTime.Hours
								% 10;
					} else {
						setAlarm.AlarmTime.Hours += 10;
					}
					break;
				}
				case 1: {
					if (setAlarm.AlarmTime.Hours >= 23) {
						setAlarm.AlarmTime.Hours = 00;
					} else {
						setAlarm.AlarmTime.Hours += 1;
					}
					break;
				}
				case 2: {
					if (setAlarm.AlarmTime.Minutes >= 50) {
						setAlarm.AlarmTime.Minutes = setAlarm.AlarmTime.Minutes
								% 10;
					} else {
						setAlarm.AlarmTime.Minutes += 10;
					}
					break;
				}
				case 3: {
					if (setAlarm.AlarmTime.Minutes >= 59) {
						setAlarm.AlarmTime.Minutes = 00;
					} else {
						setAlarm.AlarmTime.Minutes += 1;
					}
					break;
				}
				case 4: {
					if (setAlarm.AlarmTime.Seconds >= 50) {
						setAlarm.AlarmTime.Seconds = setAlarm.AlarmTime.Seconds
								% 10;
					} else {
						setAlarm.AlarmTime.Seconds += 10;
					}
					break;
				}
				case 5: {
					if (setAlarm.AlarmTime.Seconds >= 59) {
						setAlarm.AlarmTime.Seconds = 00;
					} else {
						setAlarm.AlarmTime.Seconds += 1;
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
				switch (AlarmCursor) {
				default: {
					break;
				}
				case 0: {
					if (setAlarm.AlarmTime.Hours <= 3) {
						setAlarm.AlarmTime.Hours = setAlarm.AlarmTime.Hours % 10
								+ 20;
					} else {
						if (setAlarm.AlarmTime.Hours > 3
								&& setAlarm.AlarmTime.Hours <= 9) {
							setAlarm.AlarmTime.Hours = setAlarm.AlarmTime.Hours
									% 10 + 10;
						} else {
							setAlarm.AlarmTime.Hours -= 10;
						}
					}
					break;
				}
				case 1: {
					if (setAlarm.AlarmTime.Hours <= 0) {
						setAlarm.AlarmTime.Hours = 23;
					} else {
						setAlarm.AlarmTime.Hours -= 1;
					}
					break;
				}
				case 2: {
					if (setAlarm.AlarmTime.Minutes <= 9) {
						setAlarm.AlarmTime.Minutes = setAlarm.AlarmTime.Minutes
								% 10 + 50;
					} else {
						setAlarm.AlarmTime.Minutes -= 10;
					}
					break;
				}
				case 3: {
					if (setAlarm.AlarmTime.Minutes <= 0) {
						setAlarm.AlarmTime.Minutes = 59;
					} else {
						setAlarm.AlarmTime.Minutes -= 1;
					}
					break;
				}
				case 4: {
					if (setAlarm.AlarmTime.Seconds <= 9) {
						setAlarm.AlarmTime.Seconds = setAlarm.AlarmTime.Seconds
								% 10 + 50;
					} else {
						setAlarm.AlarmTime.Seconds -= 10;
					}
					break;
				}
				case 5: {
					if (setAlarm.AlarmTime.Seconds <= 0) {
						setAlarm.AlarmTime.Seconds = 59;
					} else {
						setAlarm.AlarmTime.Seconds -= 1;
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
		// [State 7] Clear alarm
	case 7: {
		Lcd_cursor(&LCD, 0, 0);
		Lcd_string(&LCD, "Clearing alarm  ");
		HAL_Delay(500);
		Lcd_cursor(&LCD, 1, 0);
		Lcd_string(&LCD, "....            ");
		HAL_Delay(500);
		Lcd_cursor(&LCD, 1, 0);
		Lcd_string(&LCD, "........        ");
		HAL_Delay(500);
		Lcd_cursor(&LCD, 1, 0);
		Lcd_string(&LCD, "............    ");
		HAL_Delay(500);
		Lcd_cursor(&LCD, 1, 0);
		Lcd_string(&LCD, "................");
		HAL_RTC_DeactivateAlarm(&hrtc, RTC_ALARM_A);
		HAL_Delay(300);
		Lcd_clear(&LCD);
		Lcd_cursor(&LCD, 0, 0);
		Lcd_string(&LCD, "  Alarm cleared ");
		HAL_Delay(1000);
		StateChanged = 0;
		FSM_State = 0;
		break;
	}
		// [State 8] Alarm indicator
	case 8: {
		Lcd_cursor(&LCD, 0, 0);
		Lcd_string(&LCD, ALARM_TEXT);
		Lcd_cursor(&LCD, 1, 0);
		Lcd_string(&LCD, "  Press SELECT  ");
		blinkCounter++;
		if (blinkCounter >= 10) {
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6);
			blinkCounter = 0;
		}
		uint16_t raw = Read_Button(&hadc1, 10);
		if (raw != NONE) {
			ButtonIsPressed = raw;
		} else {
			if (ButtonIsPressed == SELECT) {
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1);
				FSM_State = 0;
				ButtonIsPressed = NONE;
				StateChanged = 0;
			}
		}
		break;
	}
	}
}
