/*
 * CShadesFrame.hpp
 *
 *  Created on: 26.03.2016
 *      Author: Thorsten
 */

#ifndef CSHADESFRAME_HPP_
#define CSHADESFRAME_HPP_


#include "CControlsFrame.hpp"
#include "CSystemSetup.hpp"


class CShadesFrame : public CControlsFrame {
private:
	CSystemSetup * mySystemSetup;

protected:


public:
	CShadesFrame(UTFT *newGLCD, UTouch *newTouch,  CSystemSetup * systemSetup);
	virtual ~CShadesFrame();
	virtual void display();

};




#endif /* CSHADESFRAME_HPP_ */
