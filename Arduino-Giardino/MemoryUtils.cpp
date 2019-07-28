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

#include "MemoryUtils.h"


void eepromErase(void)
{
	for (int i = 0; i < EEPROM.length(); i++) 
	{
		EEPROM.write(i, 0xFF);
	}
}

bool eepromVerifyErased(void)
{
	uint16_t unclearBytes = 0;
	uint8_t eepromValue;
	bool eepromClear;

	for (int i = 0; i < EEPROM.length(); i++)
	{
		eepromValue = EEPROM.read(i);
		if (eepromValue != 0xFF)
		{
			unclearBytes++;
		}
	}
	if (unclearBytes != 0)
	{
		eepromClear = false;
	}
	else
	{
		eepromClear = true;
	}
	return eepromClear;
}

void eepromWritePlantedDate(uint8_t y, uint8_t m, uint8_t d)
{
	eepromWriteDate(plantedEeprom, y, m, d);
}

void eepromWriteNutrientsAddedDate(uint8_t y, uint8_t m, uint8_t d)
{
	eepromWriteDate(lastNutrientsEeprom, y, m, d);
}

void eepromWriteDate(uint16_t offset, uint8_t y, uint8_t m, uint8_t d)
{
	EEPROM.write(offset + year, y);
	EEPROM.write(offset + month, m);
	EEPROM.write(offset + day, d);
}