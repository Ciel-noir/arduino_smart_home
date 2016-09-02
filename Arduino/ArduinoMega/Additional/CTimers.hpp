/*
 * CTimers.hpp
 *
 *  Created on: 05.04.2016
 *      Author: Thorsten
 */

#ifndef CTIMERS_HPP_
#define CTIMERS_HPP_

#include "CNTPService.hpp"
#include "CSystemSetup.hpp"

class CTimers{
private:
	CNTPService * myNTPService;
	CSystemSetup * mySystemSetup;

protected:

public:
	CTimers(CNTPService * ntpService, CSystemSetup * systemSetup);
};



#endif /* CTIMERS_HPP_ */
