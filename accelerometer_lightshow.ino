/*
 * Accelerometer_lightshow-- 
 *
 *
 * BlinkM connections to Arduino
 * PWR - -- gnd -- black -- Gnd
 * PWR + -- +5V -- red   -- 5V
 * I2C d -- SDA -- green -- Analog In 4
 * I2C c -- SCK -- blue  -- Analog In 5
 *
 *
 * 2012, Myles Borins
 *
 * Code built by modifying the source "BlinkMMulti"
 * by Tod E. Kurt, ThingM, http://thingm.com/
 */

#include "Wire.h"
#include "BlinkM_funcs.h"

char serInStr[30];  // array that will hold the serial input string

void setup()
{
	BlinkM_beginWithPower();

    Serial.begin(57600);
	
	BlinkM_stopScript(9); // This is so fucking janky

	BlinkM_setFadeSpeed(0, 50);
	BlinkM_fadeToRGB(0, 0, 0, 0);
}

// arduino loop func
void loop()
{
	int num;
	//read the serial port and create a string out of what you read
	if( readSerialString() ) {
		Serial.println(serInStr);
		char cmd = serInStr[0];  // first char is command
		char* str = serInStr;
		while( *++str == ' ' );  // got past any intervening whitespace
		num = atoi(str);         // the rest is arguments (maybe)
    
		if( cmd == 'c') { 
			byte a = toHex( str[0],str[1] );
			byte b = toHex( str[2],str[3] );
			byte c = toHex( str[4],str[5] );
			BlinkM_fadeToRGB(9,a,b,c);
		}
	}
}

//read a string from the serial and store it in an array
//you must supply the array variable
uint8_t readSerialString()
{
  if(!Serial.available()) {
    return 0;
  }
  delay(10);  // wait a little for serial data

  memset( serInStr, 0, sizeof(serInStr) ); // set it all to zero
  int i = 0;
  while (Serial.available()) {
    serInStr[i] = Serial.read();   // FIXME: doesn't check buffer overrun
    i++;
  }
  //serInStr[i] = 0;  // indicate end of read string
  return i;  // return number of chars read
}

// -----------------------------------------------------
// a really cheap strtol(s,NULL,16)
#include <ctype.h>
uint8_t toHex(char hi, char lo)
{
  uint8_t b;
  hi = toupper(hi);
  if( isxdigit(hi) ) {
    if( hi > '9' ) hi -= 7;      // software offset for A-F
    hi -= 0x30;                  // subtract ASCII offset
    b = hi<<4;
    lo = toupper(lo);
    if( isxdigit(lo) ) {
      if( lo > '9' ) lo -= 7;  // software offset for A-F
      lo -= 0x30;              // subtract ASCII offset
      b = b + lo;
      return b;
    } // else error
  }  // else error
  return 0;
}