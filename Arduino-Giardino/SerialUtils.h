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

// SerialUtils.h

#ifndef _SERIALUTILS_h
#define _SERIALUTILS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Constants.h"

void serialBegin(void);
void serialPrint(char* str);
void serialPrint(const char* str);
void serialPrint(uint8_t v);
void serialPrint(uint16_t v);
void serialPrint(uint32_t v);
void serialPrintln(char* str);
void serialPrintln(const char* str);
void serialPrintln(uint8_t v);
void serialPrintln(uint16_t v);
void serialPrintln(uint32_t v);

#endif

