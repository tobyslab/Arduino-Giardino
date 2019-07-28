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

#pragma once

const uint8_t relayLights = 7;
const uint8_t relayAerator = 8;
const uint8_t relayAttention = 6;
const uint8_t attentionLed = 9;
const uint8_t waterLevel = 10;
const uint8_t relayOn = LOW;
const uint8_t relayOff = HIGH;
const uint8_t relayDelay = 250;
const uint8_t buttonOk = 2;
const uint8_t buttonUp = 4;
const uint8_t buttonDown = 5;
const uint8_t buttonLight = 3;
const uint8_t log_info = 0;
const uint8_t log_warning = 1;
const uint8_t log_error = 2;

// Hours of light per type * 10
const uint8_t flowerType = 155;		// 15.5 hours
const uint8_t vegetableType = 160;	// 16 hours
const uint8_t saladType = 165;		// 16.5 hours
const uint8_t herbType = 170;		// 17 hours
const uint8_t customType = 240;		// 24 hours

// Constants
// EEPROM locations
// Sequence that the date is stored in the EEPROM
const uint8_t year = 0;
const uint8_t month = 1;
const uint8_t day = 2;
// Offset in EEPROM for the planted date
const uint16_t plantedEeprom = 0;
// Offset in the EEPROM for the last nutrients date
const uint16_t lastNutrientsEeprom = 3;
// Offset in the EEPROM for the plant type
const uint16_t plantTypeEeprom = 4;
// Days between nutrient refreshes
const uint8_t nutrientCycle = 14;