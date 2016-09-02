/*
 * CShadesFrame.cpp
 *
 *  Created on: 26.03.2016
 *      Author: Thorsten
 */

#include "CShadesFrame.hpp"

CShadesFrame::CShadesFrame(UTFT *newGLCD, UTouch *newTouch,
		 CSystemSetup * systemSetup) :
		CControlsFrame(newGLCD, newTouch, 2), mySystemSetup(systemSetup) {

}

CShadesFrame::~CShadesFrame() {

}

void CShadesFrame::display() {
	CControlsFrame::display();

}

