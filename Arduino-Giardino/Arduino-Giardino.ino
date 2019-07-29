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

// String definitions for localization etc.
#include "SerialUtils.h"
#include "I2CUtils.h"
#include "ClockUtils.h"
#include "Constants.h"
#include "LocaleStrings.h"
#include "MemoryUtils.h"
#include "LcdUtils.h"
#include "LogUtils.h"
#include "DateTimeUtils.h"

// Set to true when the lights are on
bool lightsOn = false;
volatile bool lightButtonState = 0;
// Indicates that the light has changed state within the ISR
// we don't want to log the change in the ISR (the logging datestamp uses the
// RTC and that is a no-no in the ISR
// 0 = nothing happened, 1 = toggled on 2 = toggled off
volatile uint8_t lightChangedState = 0;
// clockPeriod is the refresh rate of the RTC on the display, 
// and controls the flashing : in the time display
static int idleUpdatePeriodMs = 1000;
// days planted  and nutrient cycle display delay - controls the time between switching
// between days planted and add nutrients in x days display in ms
uint16_t displayCycleMs = 5000;
// Time between alarm updates
uint16_t alarmThrottleMs = 1000;
// These are used for non-blocking timer operations
uint32_t idleUpdateTimeNow = 0;
uint32_t displayCycleTimer = 0;
uint32_t alarmThrottleTimer = 0;
// Set to true if we are in alarm state
bool inAlarm = false;

// Arduino reset vector at address 0
void(*resetFunc) (void) = 0;

void setup() {
	uint8_t error;

	serialBegin();

	// Prevent 'bouncing' of the outputs as these relays are on when the output is low
	digitalWrite(relayLights, relayOff);
	digitalWrite(relayAerator, relayOff);
	digitalWrite(relayAttention, relayOff);

	// Set our digital pins as outputs for the relays
	pinMode(relayLights, OUTPUT);
	pinMode(relayAerator, OUTPUT);
	pinMode(relayAttention, OUTPUT);

	// These are our our four buttons, with 10k ohm pull-down resistors
	pinMode(buttonOk, INPUT);
	pinMode(buttonUp, INPUT);
	pinMode(buttonDown, INPUT);
	pinMode(buttonLight, INPUT);

	// Our attention LED
	pinMode(attentionLed, OUTPUT);
	// Water sensing pin (use a 10k ohm pull-down resistor on the input)
	pinMode(waterLevel, INPUT);

	serialPrint(appName);
	serialPrint(" ");
	serialPrint(revision);
	serialPrint(" ");
	serialPrintln(infoUrl);

	if (error)
	{
		serialPrintln(i2cErrorString);
		serialPrintln(": ");
		serialPrintln(error);
		serialPrintln(urlPrefix);
		serialPrintln(i2cerrUrl);
	}
	lcdBegin(16, 2);
	lcdSetBacklight(255);
	lcdHome();
	lcdClear();
	lcdPrint(appName);
	lcdPrintCentered(1, revision);
	delay(3000);
	lcdPrintCentered(1, infoUrl);
	delay(3000);
	lcdClear();
	serialPrintln("Ready");
	lcdHome();
	attachInterrupt(1, light_ISR, RISING);
}

void loop() {
	// Display the RTC data
	if (millis() > idleUpdateTimeNow + idleUpdatePeriodMs)
	{
		if (!inAlarm)
		{
			idleDisplay();
		}
		idleUpdateTimeNow = millis();
	}

	// You can press buttonOk and buttonLight at the same time to reset the Arduino
	if (digitalRead(buttonOk) && digitalRead(buttonLight))
	{
		resetFunc();
	}

	// See if we need to put the attention LED on for water or nutrients
	if (getDaysTillNutrients() <= 0)
	{
		if (millis() > alarmThrottleTimer + alarmThrottleMs)
		{
			if (!inAlarm)
			{
				lcdClear();
				lcdPrintCentered(0, addNutrientsString);
				alarmThrottleTimer = millis();
				logMessage(log_warning, addNutrientsString);
				digitalWrite(attentionLed, HIGH);
				digitalWrite(relayAttention, relayOn);
				inAlarm = true;
			}
		}
	}
	else if (digitalRead(waterLevel))
	{
		if (millis() > alarmThrottleTimer + alarmThrottleMs)
		{
			if (!inAlarm)
			{
				lcdClear();
				lcdPrintCentered(0, addWaterString);
				alarmThrottleTimer = millis();
				logMessage(log_warning, addWaterString);
				digitalWrite(attentionLed, HIGH);
				digitalWrite(relayAttention, relayOn);
				inAlarm = true;
			}
		}
	}
	else
	{
		digitalWrite(relayAttention, relayOff);
		digitalWrite(attentionLed, LOW);
		inAlarm = false;
	}

	// See if the light was toggled on or off, if so then log it
	char lightLog[32];
	if (lightChangedState == 1)
	{
		// Toggled on
		sprintf(lightLog, "ISR: %s %s", toggleLightString, onString);
		logMessage(log_info, lightLog);
		lightChangedState = 0;
	}
	else if (lightChangedState == 2)
	{
		// Toggled off
		sprintf(lightLog, "ISR: %s %s", toggleLightString, offString);
		logMessage(log_info, lightLog);
		lightChangedState = 0;
	}
}

void idleDisplay(void) {
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	static bool flash = 0;
	// DisplayMode 0 = days planted, 1 = days until nutrients are to be added
	static uint8_t displayMode = 0;
	uint16_t daysPlanted = getDaysPlanted();
	uint16_t daysTillNutrients = getDaysTillNutrients();

	// Display the RTC data
	// Note this will go to displayMode 1 if the startup time of the Arduino
	// is > than displayCycleMs
	if (millis() > displayCycleTimer + displayCycleMs)
	{
		displayCycleTimer = millis();
		if (displayMode == 0)
		{
			displayMode = 1;
		}
		else
		{
			displayMode = 0;
			
		}
		lcdClear();
	}

	lcdSetCursor(0, 0);

	if (displayMode == 0)
	{
		lcdPrint(daysPlantedString);
		if (daysPlanted < 100)
		{
			lcdPrint(": ");
		}
		lcdPrint(daysPlanted);
	}
	else
	{
		lcdPrint(addNutrientsString);
		lcdPrint(":");
		if (daysTillNutrients < 10)
		{
			lcdPrint(" ");
		}
		lcdPrint(daysTillNutrients);
		lcdPrint(dayShort);
	}

	lcdSetCursor(0, 1);

	char dateStr[10];
	getFormattedDate(dateStr, '/');
	lcdPrint(dateStr);
	lcdPrint(" ");

	char timeStr[4];

	if (flash)
	{
		getFormattedHourMinute(timeStr, ':');
		flash = false;
	}
	else
	{
		getFormattedHourMinute(timeStr, ' ');
		flash = true;
	}

	lcdPrint(timeStr);

	char logMsg[32];
	sprintf(logMsg, "%s: %d, %s: %d%s", 
		daysPlantedString, daysPlanted,
		addNutrientsString, daysTillNutrients,
		dayShort);

	logMessage(log_info, logMsg);
}

void addLeadingZero(uint8_t num)
{
	if (num < 10)
	{
		lcdPrint("0");
	}
	lcdPrint(num);
}

void light_ISR()
{
	static unsigned long last_interrupt_time = 0;
	unsigned long interrupt_time = millis();
	// If interrupts come faster than 200ms, assume it's a bounce and ignore
	if (interrupt_time - last_interrupt_time > 200)
	{
		if (lightsOn)
		{
			lightChangedState = 2;
			digitalWrite(relayLights, relayOff);
			lightsOn = false;
		}
		else
		{
			lightChangedState = 1;
			digitalWrite(relayLights, relayOn);
			lightsOn = true;
		}
	}
	last_interrupt_time = interrupt_time;
}
