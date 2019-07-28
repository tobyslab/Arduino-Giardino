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

#include "LcdUtils.h"

LiquidCrystal_PCF8574 lcd(0x27); // set the LCD address to 0x27 for a 16 chars and 2 line display

void lcdPrintCentered(uint8_t row, char* string)
{
	lcdSetCursor(0 + lcdGetDisplayOffset(string), row);
	lcdPrint(string);
}

uint8_t lcdGetDisplayOffset(char* string)
{
	uint8_t offset;

	offset = (uint8_t)(16 - (strlen(string))) / 2;

	return offset;
}

void lcdBegin(uint8_t col, uint8_t row)
{
	lcd.begin(col, row);
}

void lcdSetBacklight(uint8_t brightness)
{
	lcd.setBacklight(brightness);
}

void lcdHome(void)
{
	lcd.home();
}

void lcdClear(void)
{
	lcd.clear();
}

void lcdPrint(char* str)
{
	lcd.print(str);
}

void lcdPrint(const char* str)
{
  lcd.print(str);
}

void lcdPrint(uint8_t v)
{
	lcd.print(v);
}

void lcdPrint(uint16_t v)
{
	lcd.print(v);
}

void lcdPrint(uint32_t v)
{
	lcd.print(v);
}



void lcdSetCursor(uint8_t col, uint8_t row)
{
	lcd.setCursor(col, row);
}
