/*
 * RS485IO.cpp
 *
 *  Created on: 08.04.2016
 *      Author: Thorsten
 */

#include "CRS485IO.hpp"

CRS485IO::CRS485IO() {

}

CRS485IO::~CRS485IO() {

}

//getter for the sensors
int CRS485IO::getHumiditySensorValue(int sensor) {
	return 0;
	//TODO return realValue
}

int CRS485IO::getLightSensorInsideAmbientValue(int sensor) {
	return 0;
//TODO return realValue}
}

int CRS485IO::getLightSensorOutsideShadeValue(int sensor) {
	return 0;
//TODO return realValue}
}

int CRS485IO::getLightSensorOutsideAmbientValue(int sensor) {
	return 0;
//TODO return realValue}
}
