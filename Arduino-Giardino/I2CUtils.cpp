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

#include "I2CUtils.h"

void wireBegin(void)
{
	Wire.begin();
}

void wireBeginTransmission(uint8_t address)
{
	Wire.beginTransmission(address);
}

uint8_t wireEndTransmission(void)
{
	return Wire.endTransmission();
}

uint8_t wireCheckAddress(uint8_t address)
{
	wireBegin();
	wireBeginTransmission(address);
	return wireEndTransmission();
}

uint8_t checkI2cDevices()
{
	uint8_t error;

	error = wireCheckAddress(lcdAddress);
	if (!error)
	{
		error = wireCheckAddress(rtcAddress);
	}
}