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

#include "SerialUtils.h"

void serialBegin(void)
{
	Serial.begin(baudRate);
}

void serialPrint(char* str)
{
	Serial.print(str);
}

void serialPrint(const char* str)
{
	Serial.print(str);
}

void serialPrint(uint8_t v)
{
	Serial.print(v);
}

void serialPrint(uint16_t v)
{
	Serial.print(v);
}

void serialPrint(uint32_t v)
{
	Serial.print(v);
}

void serialPrintln(char* str)
{
	Serial.println(str);
}

void serialPrintln(const char* str)
{
	Serial.println(str);
}

void serialPrintln(uint8_t v)
{
	Serial.println(v);
}

void serialPrintln(uint16_t v)
{
	Serial.println(v);
}

void serialPrintln(uint32_t v)
{
	Serial.println(v);
}