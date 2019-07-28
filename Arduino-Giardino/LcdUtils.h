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

// LcdUtils.h

#ifndef _LCDUTILS_h
#define _LCDUTILS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <LiquidCrystal_PCF8574.h>

// Function prototypes
void lcdPrintCentered(uint8_t row, char* string);
uint8_t lcdGetDisplayOffset(char* string);
void lcdBegin(uint8_t col, uint8_t row);
void lcdSetBacklight(uint8_t brightness);
void lcdHome(void);
void lcdClear(void);
void lcdPrint(char* str);
void lcdPrint(const char* str);
void lcdPrint(uint8_t v);
void lcdPrint(uint16_t v);
void lcdPrint(uint32_t v);
void lcdSetCursor(uint8_t col, uint8_t row);

#endif
