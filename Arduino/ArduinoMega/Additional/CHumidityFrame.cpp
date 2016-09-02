/*
 * CHumidityFrame.cpp
 *
 *  Created on: 05.04.2016
 *      Author: Thorsten
 */


#include "CHumidityFrame.hpp"

CHumidityFrame::CHumidityFrame(UTFT *newGLCD, UTouch *newTouch,
		CSystemSetup * systemSetup, CSensorValues * sensorValues):
		CControlsFrame(newGLCD, newTouch, 3), mySystemSetup(
				systemSetup), mySensorValues(sensorValues) {

}
