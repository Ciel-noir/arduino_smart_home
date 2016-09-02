/*
 * CController.cpp
 *
 *  Created on: 25.03.2016
 *      Author: Thorsten
 */

#include "CController.hpp"

CController::CController(CRelayLogic * relayLogic, CDisplay * display,
		CManualControls * manualController, CTimers * timers,
		CSystemSetup * systemSetup, CSensorValues * sensorsValues) :
		myRelayLogic(relayLogic), myDisplay(display), myManualController(
				manualController), myTimers(timers), mySystemSetup(
				systemSetup), mySensorsValues(sensorsValues) {

}

