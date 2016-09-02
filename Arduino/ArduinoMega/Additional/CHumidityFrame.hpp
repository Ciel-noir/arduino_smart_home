/*
 * CHumidityFrame.hpp
 *
 *  Created on: 05.04.2016
 *      Author: Thorsten
 */

#ifndef CHUMIDITYFRAME_HPP_
#define CHUMIDITYFRAME_HPP_

#include "CControlsFrame.hpp"
#include "CSystemSetup.hpp"
#include "CSensorValues.hpp"

class CHumidityFrame: public CControlsFrame {
private:
	CSystemSetup * mySystemSetup;
	CSensorValues * mySensorValues;

protected:

public:
	CHumidityFrame(UTFT *newGLCD, UTouch *newTouch,
			CSystemSetup * systemSetup, CSensorValues * sensorValues);
	virtual ~CHumidityFrame();
	virtual void display();

};




#endif /* CHUMIDITYFRAME_HPP_ */
