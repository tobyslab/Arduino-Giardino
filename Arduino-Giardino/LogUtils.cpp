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

#include "LogUtils.h"

void logMessage(uint8_t type, char* message)
{
	Serial.print(clockGetYear() + 2000);
	Serial.print("-");
	logPadSingleDigit(clockGetMonth());
	Serial.print("-");
	logPadSingleDigit(clockGetDate());
	Serial.print(" ");
	logPadSingleDigit(clockGetHour());
	Serial.print(":");
	logPadSingleDigit(clockGetMinute());
	Serial.print(":");
	logPadSingleDigit(clockGetSecond());
	Serial.print(" (");
	switch (type)
	{
	case log_error:
		Serial.print("error) ");
		break;
	case log_warning:
		Serial.print("warning) ");
		break;
	case log_info:
		Serial.print("info) ");
		break;
	}
	Serial.println(message);
}

void logPadSingleDigit(uint8_t digit)
{
	if (digit < 10)
	{
		Serial.print("0");
	}
	Serial.print(digit);
}