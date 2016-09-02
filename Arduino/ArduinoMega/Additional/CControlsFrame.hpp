/*
 * CControlsFrame.hpp
 *
 *  Created on: 25.03.2016
 *      Author: Thorsten
 */

#ifndef CCONTROLSFRAME_HPP_
#define CCONTROLSFRAME_HPP_


#define FRAMESTART 27



#include "CDisplay.hpp"

#include <UTFT.h>
#include <UTFT_Buttons.h>


class CControlsFrame : public CDisplay {
	// Initialize display
	// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
protected:
	UTFT  *myGLCD;
	UTouch * myTouch;
	UTFT_Buttons  *myButtons;
	int * framebuttons;
	int buttonCount;

	//currently active menu
	int activeButton;
	const int displayXSize;
	const int displayYSize;

public:
	CControlsFrame(UTFT  *newGLCD, UTouch * newTouch, int active);
	virtual ~CControlsFrame();
	virtual void display();
	virtual void initDisplay();

};



#endif /* CCONTROLSFRAME_HPP_ */
