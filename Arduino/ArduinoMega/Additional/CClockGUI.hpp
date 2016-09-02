/*
 * CClockDisplay.hpp
 *
 *  Created on: 20.03.2016
 *      Author: Thorsten
 */

#ifndef ADDITIONAL_CCLOCKDISPLAY_HPP_
#define ADDITIONAL_CCLOCKDISPLAY_HPP_
#include "CDisplay.hpp"

#include <UTFT.h>



class CClockGUI: public CDisplay {
	// Initialize display
	// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
private:
	UTFT  *myGLCD;


public:
	CClockGUI(UTFT  *newGLCD);
	virtual ~CClockGUI();
	virtual void initDisplay();
	virtual void display();



protected:
	String normalizeDigits(int digits);

};

#endif /* ADDITIONAL_CCLOCKDISPLAY_HPP_ */
