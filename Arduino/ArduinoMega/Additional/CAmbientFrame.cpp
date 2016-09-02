/*
 * CAmbientFrame.cpp
 *
 *  Created on: 26.03.2016
 *      Author: Thorsten
 */

#include "CAmbientFrame.hpp"

CAmbientFrame::CAmbientFrame(UTFT *newGLCD, UTouch *newTouch,
	 CSystemSetup * systemSetup, CSensorValues * sensorValues) :
		CControlsFrame(newGLCD, newTouch, 1), mySystemSetup(
				systemSetup), mySensorValues(sensorValues) {

}

CAmbientFrame::~CAmbientFrame() {

}

void CAmbientFrame::display() {
	CControlsFrame::display();

}
