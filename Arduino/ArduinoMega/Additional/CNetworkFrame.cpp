/*
 * CNetworkFrame.cpp
 *
 *  Created on: 05.04.2016
 *      Author: Thorsten
 */

#include "CNetworkFrame.hpp"

CNetworkFrame::CNetworkFrame(UTFT * tft, UTouch * touch,
		 CSystemSetup * systemSetup) :
		CControlsFrame(tft, touch, 4), mySystemSetup(
				systemSetup)
{

}
