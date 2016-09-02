/*
 * CWireIO.cpp
 *
 *  Created on: 05.04.2016
 *      Author: Thorsten
 */

#include "CWireIO.hpp"

CWireIO::CWireIO(byte adress, byte slaves[], byte slaveCount) :
		myAdress(adress), mySlaveCount(slaveCount), mySlaves(slaves) {

}




/*
 * returns the value of an inside ambient light sensor
 */
int CWireIO::getLightSensorInsideAmbientValue(int sensor) {
	//if value of more than configured sensors called
	if (sensor >= this->lightSensorCount) {
		return -1;
	}

	//----------------------------------------------------------------------------TODO Test only
		return 0;
}

/*
 * returns the value of an inside shade light sensor
 */
int CWireIO::getLightSensorOutsideShadeValue(int sensor) {
	//if value of more than configured sensors called
	if (sensor >= this->lightSensorCount) {
		return -1;
	}

	//----------------------------------------------------------------------------TODO Test only
	return 0;
}

/*
 * returns the value of an outside ambient light sensor
 */
int CWireIO::getLightSensorOutsideAmbientValue(int sensor) {
	//if value of more than configured sensors called
	if (sensor >= this->lightSensorCount) {
		return -1;
	}

	//----------------------------------------------------------------------------TODO Test only
		return 0;
}

/*
 * returns the value of an humidity sensor
 */
int CWireIO::getHumiditySensorValue(int sensor) {
	//if value of more than configured sensors called
	if (sensor >= this->humiditySensorCount) {
		return -1;
	}

	//----------------------------------------------------------------------------TODO Test only
		return 0;
}
