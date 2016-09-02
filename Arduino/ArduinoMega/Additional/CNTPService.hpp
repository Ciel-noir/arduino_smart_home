/*
 * CNTPService.hpp
 *
 *  Created on: 05.04.2016
 *      Author: Thorsten
 */

#ifndef CNTPSERVICE_HPP_
#define CNTPSERVICE_HPP_

#include "CWireIO.hpp"
#include "CSystemSetup.hpp"

class CNTPService{
private:
	CWireIO * myWireConnection;
	CSystemSetup * mySytemSetup;

protected:

public:
	CNTPService(CWireIO * wire, CSystemSetup * systemSetup);
};



#endif /* CNTPSERVICE_HPP_ */
