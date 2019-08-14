/*
	Arduino Giardino
	Copyright (C) 2019 Toby Boreham. https://tlab.co/ag

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "DateTimeUtils.h"


uint32_t getJulianDate(uint16_t y, uint16_t m, uint16_t d)
{
	// Code from: https://pdc.ro.nu/jd-code.html
	y += 8000;
	if (m < 3) { y--; m += 12; }
	return (y * 365) + (y / 4) - (y / 100) + (y / 400) - 1200820
		+ (m * 153 + 3) / 5 - 92
		+ d - 1;
}

uint32_t getJulianFromClock(void)
{
	uint8_t todayMonth = clockGetMonth();
	uint8_t todayDay = clockGetDate();
	uint8_t todayYear = clockGetYear();
	uint32_t todayJulian = getJulianDate(2000 + todayYear, todayMonth, todayDay);

	return todayJulian;
}

uint16_t getDaysPlanted(void)
{
	uint32_t todayJulian = getJulianFromClock();
	uint32_t plantedJulian = getJulianFromEeprom(plantedEeprom);
	uint16_t daysPlanted = todayJulian - plantedJulian;

	return daysPlanted;
}

uint16_t getDaysTillNutrients(void)
{
	uint32_t todayJulian = getJulianFromClock();
	uint32_t nutrientsJulian = getJulianFromEeprom(lastNutrientsEeprom);
	int16_t daysTillNutrients = nutrientCycle - (todayJulian - nutrientsJulian);
	
	if (daysTillNutrients < 0)
	{
		daysTillNutrients = 0;
	}

	return (uint16_t) daysTillNutrients;
}

uint32_t getJulianFromEeprom(uint16_t offset)
{
	uint8_t eepromMonth = EEPROM.read(offset + month);
	uint8_t eepromDay = EEPROM.read(offset + day);
	uint8_t eepromYear = EEPROM.read(offset + year);
	uint32_t eepromJulian = getJulianDate(2000 + eepromYear, eepromMonth, eepromDay);

	return eepromJulian;
}

void getFormattedDate(char* str, char sep)
{
	uint8_t month = clockGetMonth();
	uint8_t day = clockGetDate();
	uint16_t year = clockGetYear();

	sprintf(str, "%02d%c%02d%c20%02d", month, sep, day, sep, year);
}

void getFormattedHourMinute(char* str, char sep)
{
	uint8_t hour = clockGetHour();
	uint8_t minute = clockGetMinute();

	sprintf(str, "%02d%c%02d", hour, sep, minute);
}