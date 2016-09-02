/*
 * CAmbientFrame.hpp
 *
 *  Created on: 26.03.2016
 *      Author: Thorsten
 */

#ifndef CAMBIENTFRAME_HPP_
#define CAMBIENTFRAME_HPP_

#include "CControlsFrame.hpp"
#include "CSystemSetup.hpp"
#include "CSensorValues.hpp"

class CAmbientFrame: public CControlsFrame {
private:
	CSystemSetup * mySystemSetup;
	CSensorValues * mySensorValues;

protected:

public:
	CAmbientFrame(UTFT *newGLCD, UTouch *newTouch,
			CSystemSetup * systemSetup, CSensorValues * sensorValues);
	virtual ~CAmbientFrame();
	virtual void display();

};

#endif /* CAMBIENTFRAME_HPP_ */
