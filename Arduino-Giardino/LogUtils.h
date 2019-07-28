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

// LogUtils.h

#ifndef _LOGUTILS_h
#define _LOGUTILS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "LocaleStrings.h"
#include "Constants.h"
#include "ClockUtils.h"

void logMessage(uint8_t type, char* message);
void logPadSingleDigit(uint8_t digit);

#endif

