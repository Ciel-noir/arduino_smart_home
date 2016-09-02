/*
 * CDisplay.h
 *
 *  Created on: 20.03.2016
 *      Author: Thorsten
 */

#ifndef HEADER_CDISPLAY_H_
#define HEADER_CDISPLAY_H_

#include <UTFT.h>
#include <Time.h>


class CDisplay {

public:
	virtual ~CDisplay() {};
	virtual void initDisplay() = 0;
	virtual void display() = 0;
};


#endif /* HEADER_CDISPLAY_H_ */
