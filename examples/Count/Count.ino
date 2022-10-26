/*	Example sketch using the DoubleSevenSegment library
			to display a countup on a 2 digit 7 segment display.

		https://github.com/Skkeye/DoubleSevenSegment

		Version History:
			1.0.0			10/25/2022		Original
 */
#include "DoubleSevenSegment.h"

// Define the output pins to interface with the display
#define PIN_Display_Units A0
#define PIN_Display_Tens A1
#define PIN_A 15
#define PIN_B 32
#define PIN_C 14
#define PIN_D 12
#define PIN_E 13
#define PIN_F 33
#define PIN_G 27

// Display constructor
DoubleSevenSegment dss(	PIN_Display_Units, 
												PIN_Display_Tens, 
												PIN_A, 
												PIN_B, 
												PIN_C, 
												PIN_D,
												PIN_E,
												PIN_F,
												PIN_G);

void setup()
{
	Serial.begin(115200);
}

void loop()
{
	for(int i = 0; i < 100; i++)
	{
		Serial.print("Number: ");
		Serial.println(i);
		// show(number(0-99), time(ms))
		dss.show(i,100);
	}
}
