/*
 * CController.hpp
 *
 *  Created on: 25.03.2016
 *      Author: Thorsten
 */

#ifndef CCONTROLLER_HPP_
#define CCONTROLLER_HPP_

#include "CManualControl.hpp"
#include "CDisplay.hpp"
#include "CTimers.hpp"
#include "CRelayLogic.hpp"
#include "CSystemSetup.hpp"
#include "CSensorValues.hpp"

class CController {
private:
	CRelayLogic * myRelayLogic;
	CDisplay * myDisplay;
	CManualControls * myManualController;
	CTimers * myTimers;
	CSystemSetup * mySystemSetup;
	CSensorValues * mySensorsValues;

protected:

public:
	CController(CRelayLogic * relayLogic, CDisplay * display,
			CManualControls * manualController, CTimers * timers,
			CSystemSetup * systemSetup, CSensorValues * sensorsValues);
};

#endif /* CCONTROLLER_HPP_ */
