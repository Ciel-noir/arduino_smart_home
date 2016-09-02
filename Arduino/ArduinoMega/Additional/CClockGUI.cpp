/*
 * CClockGUI.cpp
 *
 *  Created on: 20.03.2016
 *      Author: Thorsten
 */

#include "CClockGUI.hpp"

CClockGUI::CClockGUI(UTFT *newGLCD) {
	myGLCD = newGLCD;

}

CClockGUI::~CClockGUI() {
	this->myGLCD = NULL;
}

void CClockGUI::initDisplay() {
	this->myGLCD->setBackColor(VGA_BLACK);
	this->myGLCD->setColor(VGA_BLACK);
	this->myGLCD->fillRect(0, 0, 319, 239);
}

void CClockGUI::display() {
	String output;

	output = this->normalizeDigits(hour());
	output += ':';
	output += this->normalizeDigits(minute());
	output += ':';
	output += this->normalizeDigits(second());

	myGLCD->setColor(VGA_WHITE);
	myGLCD->setBackColor(VGA_BLACK);

	myGLCD->print(output, 60, 50);

	output = this->normalizeDigits(day());
	output += '.';
	output += this->normalizeDigits(month());
	output += '.';
	output += this->normalizeDigits(year());
	myGLCD->print(output, 40, 130);

}

String CClockGUI::normalizeDigits(int digits) {
	// utility for digital clock display: prints preceding colon and leading 0
	String retString;
	if (digits < 10)
		retString = String('0');
	retString += String(digits);
	return retString;
}
