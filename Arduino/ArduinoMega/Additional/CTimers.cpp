/*
 * CTimers.cpp
 *
 *  Created on: 05.04.2016
 *      Author: Thorsten
 */

#include "CTimers.hpp"

CTimers::CTimers(CNTPService * ntpService, CSystemSetup * systemSetup) :
		myNTPService(ntpService), mySystemSetup(systemSetup) {

}
