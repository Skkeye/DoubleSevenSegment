/*	Library for using a 2 digits 7 segment display with multiplexing

		https://github.com/Skkeye/DoubleSevenSegment

		The library supports both common anode and cathode 2 digits 7 segment displays
			with both high and low logic levels.

		Version History:
			1.0.0			10/25/2022		Original
 */
#ifndef DoubleSevenSegment_h
#define DoubleSevenSegment_h

#include <Arduino.h>

class DoubleSevenSegment
{
	public:
		// General constructor
		DoubleSevenSegment(	int pinDisplayUnits, 
												int pinDisplayTens,
												int pinA,
												int pinB,
												int pinC,
												int pinD,
												int pinE,
												int pinF,
												int pinG,
												bool segmentOnLogicLevel = 0,
												bool commonOnLogicLevel = 0);
		
		// Method for displaying a 2 digit number.
		// optionnal : Set a display time in ms
		void show(int num, int ms = 1);
	private:
		// Lookup for standard 7 segment digits :
		//	1				: On
		//	0				: Off
		//	Format	: {A,B,C,D,E,F,G}
		int _decodeLookup[10][7] = 	{ {1,1,1,1,1,1,0},
																	{0,1,1,0,0,0,0},
																	{1,1,0,1,1,0,1},
																	{1,1,1,1,0,0,1},
																	{0,1,1,0,0,1,1},
																	{1,0,1,1,0,1,1},
																	{1,0,1,1,1,1,1},
																	{1,1,1,0,0,0,0},
																	{1,1,1,1,1,1,1},
																	{1,1,1,0,0,1,1} };
		
		// Internal propreties
		int _pinDisplayUnits;
		int _pinDisplayTens;
		int _pins[7];
		bool _segmentOnLogicLevel;
		bool _commonOnLogicLevel;
		
		// Internal method for clearing the display
		void _clear();
};

#endif
