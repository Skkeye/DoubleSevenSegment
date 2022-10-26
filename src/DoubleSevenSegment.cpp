/*	Library for using a 2 digits 7 segment display with multiplexing

		https://github.com/Skkeye/DoubleSevenSegment

		The library supports both common anode and cathode 2 digits 7 segment displays
			with both high and low logic levels.

		Version History:
			1.0.0			10/25/2022		Original
 */
#include "DoubleSevenSegment.h"
#include <stdlib.h>

// General constructor
DoubleSevenSegment::DoubleSevenSegment(	int pinDisplayUnits, 
																					int pinDisplayTens,
																					int pinA,
																					int pinB,
																					int pinC,
																					int pinD,
																					int pinE,
																					int pinF,
																					int pinG,
																					bool segmentOnLogicLevel = 0,
																					bool commonOnLogicLevel = 0)
{
	_pinDisplayUnits = pinDisplayUnits;
	_pinDisplayTens = pinDisplayTens;
	_pins[0] = pinA;
	_pins[1] = pinB;
	_pins[2] = pinC;
	_pins[3] = pinD;
	_pins[4] = pinE;
	_pins[5] = pinF;
	_pins[6] = pinG;
	_segmentOnLogicLevel = segmentOnLogicLevel;
	_commonOnLogicLevel = commonOnLogicLevel;

	// Setup the pins
	pinMode(_pinDisplayUnits, OUTPUT);
	pinMode(_pinDisplayTens, OUTPUT);
	for(int pin : _pins)
	{
		pinMode(pin, OUTPUT);
	}

	// Clear the display
	_clear();
}

// Method for displaying a 2 digit number.
// optionnal : Set a display time in ms
void DoubleSevenSegment::show(int num, int ms = 1)
{
	// Truncate the number to a number between 0 and 99 inclusive and keep it positive
	num = abs(num) % 100;

	// Each iteration is about 1ms long, 
	// 	so the number of iterations to perform is the ms argument
	for (int x = 0; x < ms; x++)
	{
		// Activate the units pin
		digitalWrite(_pinDisplayUnits, _commonOnLogicLevel);
		digitalWrite(_pinDisplayTens, !_commonOnLogicLevel);
		for(int i = 0; i < 7; i++)
		{
			// For each pins, get the digit in the lookup
			// 	and invert it if the on logic level is 0
			// 	(in the lookup : active = 1)
			digitalWrite(_pins[i], !_segmentOnLogicLevel ^ _decodeLookup[num % 10][i]);
		}
		// Delay to let the display settle
		delayMicroseconds(500);
		// Repeat for the tens digit
		digitalWrite(_pinDisplayUnits, !_commonOnLogicLevel);
		digitalWrite(_pinDisplayTens, _commonOnLogicLevel);
		for(int i = 0; i < 7; i++)
		{
			digitalWrite(_pins[i], !_segmentOnLogicLevel ^ _decodeLookup[num % 10][i]);
		}
		delayMicroseconds(500);
	}
	_clear();
}

// Internal method for clearing the display
void DoubleSevenSegment::_clear()
{
	digitalWrite(_pinDisplayUnits, !_commonOnLogicLevel);
	digitalWrite(_pinDisplayTens, !_commonOnLogicLevel);
	for(int pin : _pins)
	{
		digitalWrite(pin, !_segmentOnLogicLevel);
	}
}
