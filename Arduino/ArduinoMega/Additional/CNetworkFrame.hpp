/*
 * CNetworkFrame.hpp
 *
 *  Created on: 05.04.2016
 *      Author: Thorsten
 */

#ifndef CNETWORKFRAME_HPP_
#define CNETWORKFRAME_HPP_

#include "CSystemSetup.hpp"
#include "CControlsFrame.hpp"

class CNetworkFrame : public CControlsFrame {
private:
	CSystemSetup * mySystemSetup;
protected:

public:
 CNetworkFrame(UTFT * tft, UTouch * touch,
			 CSystemSetup * systemSetup);

};



#endif /* CNETWORKFRAME_HPP_ */
