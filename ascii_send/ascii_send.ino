/*
 * Music 220a Lab 2 
 * Myles Borins
 * 	
 *(╯°□°)╯︵ ┻━┻
 */ 
	 
// Initial Pin Settings
int switchPin = 2;
int accxPin = 0;
int accyPin = 1;
int acczPin = 2;
int forcePin = 5;

// Set things up
int switchState = 0;
int forceState = 0;
int accelX = 0;
int accelY = 0;
int accelZ = 0;

void setup(){
	// Set pins as inputs
	pinMode(2, INPUT);   // digital sensor is on digital pin 2
	
	// Start serial like a gentleman
	Serial.begin(57600);
}

void loop(){
	pollSwitch();
	delay(1);
	pollAccelerometer();
	delay(1);
	pollForce();
	delay(10);
}

void pollSwitch(){
	int reading = digitalRead(switchPin);
	
	if(reading != switchState){
		switchState = reading;
		Serial.print('a');
		Serial.print(' ');
		Serial.println(switchState);
	}
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

void pollForce(){
	forceState = analogRead(forcePin);
	
	Serial.print('c');
	Serial.print(' ');
	Serial.println(forceState);
}
