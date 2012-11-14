/*
 * Music 220a Lab 2 
 * Myles Borins
 * 	
 *(╯°□°)╯︵ ┻━┻
 */ 
	 
// Initial Pin Settings
int accxPin = 0;
int accyPin = 1;
int acczPin = 2;

// Set things up
int accelX = 0;
int accelY = 0;
int accelZ = 0;

void setup(){
	// Start serial like a gentleman
	Serial.begin(57600);
}

void loop(){
	pollAccelerometer();
	delay(10);
}

void pollAccelerometer(){
	accelX = analogRead(accxPin);
	accelY = analogRead(accyPin);
	accelZ = analogRead(acczPin);
	
	Serial.print('b');
	Serial.print(' ');
	Serial.print(accelX);
	Serial.print(' ');
	Serial.print(accelY);
	Serial.print(' ');
	Serial.println(accelZ);
}
