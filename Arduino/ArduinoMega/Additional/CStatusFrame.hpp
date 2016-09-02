/*
 * CStatusFrame.hpp
 *
 *  Created on: 05.04.2016
 *      Author: Thorsten
 */

#ifndef CSTATUSFRAME_HPP_
#define CSTATUSFRAME_HPP_


#include "CControlsFrame.hpp"
#include "CSystemSetup.hpp"
#include "CSensorValues.hpp"

class CStatusFrame: public CControlsFrame {
private:
	CSystemSetup * mySystemSetup;
	CSensorValues * mySensorValues;

protected:

public:
	CStatusFrame(UTFT * tft, UTouch * touch,
			CSystemSetup * systemSetup, CSensorValues * sensorValues);
	virtual ~CStatusFrame();
	virtual void display();
	virtual void initDisplay();

	void updateDisplay();

	void drawSimpleLightPanel(int x, int y);
	void drawSimpleShadesPanel(int x, int y);
	void drawSimpleTempPanel(int x, int y);
	void drawSimpleHumidityPanel(int x, int y);

	void drawSingleHumidityIndication(int x, int y);
	void drawSimpleLightIndication(int x, int y);
	void drawSimpleShadeIndication(int x, int y);

	void updateValues();
};

#endif /* CSTATUSFRAME_HPP_ */
