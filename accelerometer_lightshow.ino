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
 *
 *(╯°□°)╯︵ ┻━┻
 */

#include "Wire.h"
#include "BlinkM_funcs.h"

// Initial Pin Settings
int accxPin = 0;
int accyPin = 1;
int acczPin = 2;

// Set things up
int accelX = 0;
int accelY = 0;
int accelZ = 0;

// Message system Tester vars

int LedPin = 13;
int stop = 0;
int VarSign = 1;
int SerIn = -1;          // incoming byte from serial RX
long VarN[9] = {  
  0, 0, 0, 0, 0, 0, 0, 0, 0 };      // number array
int PosN = -1;       // index counter
char VarHandlerChar = '@';       //

void setup(void) {
  BlinkM_beginWithPower();
  
  Serial.begin(115200);                 // Serialle Schnittstelle mit 115200 Baud

  BlinkM_stopScript(9); // This is so fucking janky
  
  BlinkM_setFadeSpeed(0, 70);
  BlinkM_fadeToRGB(0, 0, 0, 0);
}

void loop(void) {
  SerialParser();
}

// SERIAL PARSER **********************************
void SerialParser(void) {
  while (Serial.available()) {
    SerIn = '@';
    SerIn = Serial.read();
    // debugging CODE
    // Serial.print(' ');
    // Serial.print(SerIn);
    if ((SerIn >= 65) && (SerIn <= 90)) {          // if ASCII 'A' - 'Z'
      VarHandlerChar = SerIn;  
      for (PosN = 0; PosN < 9; PosN++) {           // clean up
        VarN[PosN] =  0;                           // reset Var array
      }  
      PosN = -1;                              
    }
    if (SerIn == 45) {
      VarSign = -1;
    }
    if ((SerIn >= 48) && (SerIn <= 57)) {          // if ASCII numeric '0' - '9'
      VarN[PosN] = VarN[PosN] * 10 + (SerIn - 48);
    }
    if (SerIn == ' ') {                            // if ASCII " " detected
      if (PosN > -1) {
        VarN[PosN] = VarSign * VarN[PosN];           // assign sign
        VarSign = 1;
      }
      PosN++;
    }
    if (SerIn == 33 || SerIn == 10 || SerIn == 13) {  // '!' or CR or LF ends all this spooky things ...
      VarN[PosN] = VarSign * VarN[PosN];           // assign sign
      VarSign = 1;
      CallHandler();                               // Call funktion by first Char
    }   // IfEND CR spooky things
  }
}

// CALLHANDLER SCHEDULER ******************************
// which of YOUR functions are called?
//

void CallHandler(void) {
  switch(VarHandlerChar) {
	  case 'Z': // do something when A
    
      // Add an if statement to check that array is correct length
      BlinkM_fadeToRGB(9, VarN[0], VarN[1], VarN[2]);
	    break;    
	  case 'Y':  // do something when B
	    DebugOut();
	    break;        
	  } // Switch END
}

//
// CALLHANDLER FUNCTIONS *******************************
// YOUR funktions here:

void DebugOut(void) {
  //Serial.print("got an: ");
  
  Serial.write(VarHandlerChar);
  for (int  i = 0; i < PosN; i++) {
    Serial.print(' ');
    Serial.print(VarN[i]);
  }
  Serial.println(" !");
}