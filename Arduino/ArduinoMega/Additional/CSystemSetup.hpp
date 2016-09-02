/*
 * CSystemSettings.hpp
 *
 *  Created on: 05.04.2016
 *      Author: Thorsten
 */

#ifndef CSYSTEMSETUP_HPP_
#define CSYSTEMSETUP_HPP_

#include "CSDCardIO.hpp"

class CSystemSetup {
private:
	CSDCardIO * mySDCard;
protected:

public:
	CSystemSetup(CSDCardIO * sdCardIO);

};

#endif /* CSYSTEMSETTINGS_HPP_ */
