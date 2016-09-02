/*
 * CWireIO.hpp
 *
 *  Created on: 05.04.2016
 *      Author: Thorsten
 */

#ifndef CWIREIO_HPP_
#define CWIREIO_HPP_

#include "Arduino.h"

class CWireIO {
private:
	byte myAdress;
	byte mySlaveCount;
	byte * mySlaves;

	//counts of sensors connected -> all situated in the kitchen
	const int lightSensorCount = 3;
	const int humiditySensorCount = 4;

protected:

public:
	CWireIO(byte adress, byte slaves[], byte slaveCount);


	//getter for the sensors
	int getHumiditySensorValue(int sensor);
	int getLightSensorInsideAmbientValue(int sensor);
	int getLightSensorOutsideShadeValue(int sensor);
	int getLightSensorOutsideAmbientValue(int sensor);


};



#endif /* CWIREIO_HPP_ */
