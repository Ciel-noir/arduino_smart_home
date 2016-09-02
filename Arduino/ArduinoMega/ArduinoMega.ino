#include <UTFT.h>
#include <Arduino.h>
#include <UTouch.h>
#include <UTFT_Buttons.h>
#include <TimeLib.h>
#include <Wire.h>
#include "Additional/I2C_Anything.h"
#include "Additional/CDisplay.hpp"
#include "Additional/CClockGUI.hpp"
#include "Additional/CControlsFrame.hpp"
#include "Additional/CStatusFrame.hpp"

// Initialize display
// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
//UTFT myGLCD(ITDB32S, 38, 39, 40, 41);
const int displayXSize = 240;
const int displayYSize = 320;
// Initialize touchscreen
// Standard Arduino Mega/Due shield            :  6, 5, 4, 3, 2

UTouch * myTouch;

extern uint8_t GroteskBold24x48[];
CDisplay *myDisplay;
CDisplay *prev;
//address of the slave
int ethernetShieldAddress = 2;

//Used to store the NTP time
unsigned long secsSince1900 = 0;
const int syncInterval = 15;
const int timeZone = 1;     // Central European Time

time_t prevDisplay = 0; // when the digital clock was displayed
time_t screenSaverOff = 0;

int x, y;
char stCurrent[20] = "";
int stCurrentLen = 0;
char stLast[20] = "";
UTFT *myGLCD;

time_t getNtpTime() {

	// SEND COMMAND
	Wire.beginTransmission(ethernetShieldAddress);
	Wire.write(4); // Transfer command ("1") to get X sensor value;
	delay(10);

	// GET RESPONSE
	unsigned long anotherLongInt = 0;
	int available = Wire.requestFrom(ethernetShieldAddress, (int) 4);

	if (available == 4) {
		byte buffer[4];
		buffer[0] = Wire.read();
		buffer[1] = Wire.read();
		buffer[2] = Wire.read();
		buffer[3] = Wire.read();
		Serial.println(buffer[0]);
		Serial.println(buffer[1]);
		Serial.println(buffer[2]);
		Serial.println(buffer[3]);
		anotherLongInt = (((uint32_t) buffer[0] << 24)
				+ ((uint32_t) buffer[1] << 16) + ((uint32_t) buffer[2] << 8)
				+ ((uint32_t) buffer[3]));
		// receivedValue = Wire.read() << 8 | Wire.read() << 8 | Wire.read() << 8 | Wire.read() << 8 | Wire.read(); // combine two bytes into integer
	} else {
		Serial.print(
				"ERROR: Unexpected number of bytes received (XSensorValue): ");
		Serial.println(available);
	}
	Wire.endTransmission();

	return anotherLongInt;

	secsSince1900 = anotherLongInt;
	Serial.print("NTP ");
	Serial.print("Time: ");

	//Used to store the NTP time
	Serial.print(secsSince1900);
	Serial.println();
	return secsSince1900 + 7;
}

void setup() {
	myTouch = new UTouch(6, 5, 4, 3, 2);

	myGLCD = new UTFT(ITDB32S, 38, 39, 40, 41);

	myGLCD->InitLCD();
	myGLCD->clrScr();
	myGLCD->setFont(GroteskBold24x48);

	Serial.print("Setup");
	Serial.println();

	myTouch->InitTouch();
	myTouch->setPrecision(PREC_MEDIUM);

//	myDisplay = new CClockGUI(myGLCD);
	myDisplay = new CStatusFrame(myGLCD, myTouch, NULL, NULL);
	Serial.begin(9600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for Leonardo only
	}

	Wire.begin();

	setSyncInterval(syncInterval);
	setSyncProvider(getNtpTime);
}



void loop() {
	myDisplay->display();
	if (myDisplay != prev) {
		prev = myDisplay;
		myDisplay->initDisplay();
	}
/*
	if (timeStatus() != timeNotSet) {

		if (now() != prevDisplay) { //update the display only if time has changed
			prevDisplay = now();


				myDisplay->display();
		}

		if (now() >= screenSaverOff) {
			delete myDisplay;
			myDisplay = new CClockGUI(myGLCD);
		}
	}

	if (myTouch->dataAvailable() == true) {
		prev = myDisplay;
		delete myDisplay;
		myDisplay = new CStatusFrame(myGLCD, myTouch, NULL, NULL);
		myDisplay->display();
		screenSaverOff = now() + 15;


		myDisplay->initDisplay();


	}*/

}

