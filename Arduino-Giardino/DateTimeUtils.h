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

// DateTimeUtils.h

#ifndef _DATETIMEUTILS_h
#define _DATETIMEUTILS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Constants.h"
#include "ClockUtils.h"
#include "MemoryUtils.h"

uint32_t getJulianDate(uint16_t y, uint16_t m, uint16_t d);
uint32_t getJulianFromClock(void);
uint16_t getDaysPlanted(void);
uint16_t getDaysTillNutrients(void);
uint32_t getJulianFromEeprom(uint16_t offset);
void getFormattedDate(char* str, char sep);
void getFormattedHourMinute(char* str, char sep);

#endif

