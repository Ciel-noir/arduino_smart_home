/*
 * CNTPService.cpp
 *
 *  Created on: 05.04.2016
 *      Author: Thorsten
 */

#include "CNTPService.hpp"

CNTPService::CNTPService(CWireIO * wire, CSystemSetup * systemSetup){
 this->myWireConnection = wire;
 this->mySytemSetup = systemSetup;
}


