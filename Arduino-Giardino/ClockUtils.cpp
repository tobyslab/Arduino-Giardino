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

#include "ClockUtils.h"

// DS3231 Clock variables
DS3231 Clock;
bool h12;
bool PM;
bool Century = false;

uint8_t clockGetMonth(void)
{
	return Clock.getMonth(Century);
}

uint8_t clockGetDate(void)
{
	return Clock.getDate();
}

uint8_t clockGetYear(void)
{
	return Clock.getYear();
}

uint8_t clockGetHour(void)
{
	return Clock.getHour(h12, PM);
}

uint8_t clockGetMinute(void)
{
	return Clock.getMinute();
}

uint8_t clockGetSecond(void)
{
	return Clock.getSecond();
}