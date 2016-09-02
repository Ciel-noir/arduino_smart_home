/*
 * CSensorsValues.cpp
 *
 *  Created on: 05.04.2016
 *      Author: Thorsten
 */

#include "CSensorValues.hpp"

//Constructor
CSensorValues::CSensorValues(CWireIO * wire,
		CRS485IO * rs485IO) :
		myWireIO(wire),myRS485IO(rs485IO), lightSensorCount(
				4), lightSensorConnectedCount(3), humiditySensorCount(6), humiditySensorConnectedCount(
				2) {

	//the values of the sensors
	this->lightSensorInsideAmbient = new int[lightSensorCount];
	this->lightSensorOutsideShade = new int[lightSensorCount];
	this->lightSensorOutsideAmbient = new int[lightSensorCount];
	this->humiditySensor = new int[humiditySensorCount];

	//status of the values
	this->lightSensorInsideAmbientStatus =
			new CSensorValues::SENSOR_STATUS[lightSensorCount];
	this->lightSensorOutsideAmbientStatus =
			new CSensorValues::SENSOR_STATUS[lightSensorCount];
	this->lightSensorOutsideShadeStatus =
			new CSensorValues::SENSOR_STATUS[lightSensorCount];
	this->humiditySensorStatus =
			new CSensorValues::SENSOR_STATUS[humiditySensorCount];

	//init Values
	//light
	for (int i = 0; i < this->lightSensorCount; i++) {
		this->lightSensorInsideAmbient[i] = 0;
		this->lightSensorOutsideAmbient[i] = 0;
		this->lightSensorOutsideShade[i] = 0;
		this->lightSensorInsideAmbientStatus[i] = CSensorValues::UNAVAILABLE;
		this->lightSensorOutsideAmbientStatus[i] = CSensorValues::UNAVAILABLE;
		this->lightSensorOutsideShadeStatus[i] = CSensorValues::UNAVAILABLE;
	}
	//humidity
	for (int i = 0; i < this->humiditySensorCount; i++) {
		this->humiditySensor[i] = 0;
		this->humiditySensorStatus[i] = CSensorValues::UNAVAILABLE;
	}

	//callback function pointers
	for (int i = 0; i < this->lightSensorCount; i++) {
		this->lightUpdateFunctionPointers[i] = NULL;
	}

	for (int i = 0; i < this->humiditySensorCount; i++) {
		this->humidityUpdateFunctionPointers[i] = NULL;
	}

}

//Destructor
CSensorValues::~CSensorValues() {
	delete this->lightSensorInsideAmbient;
	delete this->lightSensorOutsideShade;
	delete this->lightSensorOutsideAmbient;
	delete this->humiditySensor;
	delete this->lightSensorInsideAmbientStatus;
	delete this->lightSensorOutsideAmbientStatus;
	delete this->lightSensorOutsideShadeStatus;
	delete this->humiditySensorStatus;

	this->lightSensorInsideAmbient = NULL;
	this->lightSensorOutsideShade = NULL;
	this->lightSensorOutsideAmbient = NULL;
	this->humiditySensor = NULL;
	this->lightSensorInsideAmbientStatus = NULL;
	this->lightSensorOutsideAmbientStatus = NULL;
	this->lightSensorOutsideShadeStatus = NULL;
	this->humiditySensorStatus = NULL;

}

//updates the sensor values
void CSensorValues::updateValues() {
	//get values of the directly connected sensor
	//light
	int lightSensor = 0;

	for (; lightSensor < this->lightSensorConnectedCount; lightSensor++) {
		bool updated = false;

		//TODO
		int value = 0;

		//check if different value
		if (value != this->lightSensorInsideAmbient[lightSensor]) {
			updated = true;
		}

		if (value < 1) {
			this->lightSensorInsideAmbient[lightSensor] = 0;
			this->lightSensorInsideAmbientStatus[lightSensor] =
					(SENSOR_STATUS) ++value;

		} else {
			this->lightSensorInsideAmbientStatus[lightSensor] =
					CSensorValues::AVAILABLE;
			this->lightSensorInsideAmbient[lightSensor] = value;
		}

		//TODO
		value = 0;

		//check if different value
		if (value != this->lightSensorOutsideAmbient[lightSensor]) {
			updated = true;
		}

		if (value < 1) {
			this->lightSensorOutsideAmbient[lightSensor] = 0;
			this->lightSensorOutsideAmbientStatus[lightSensor] =
					(SENSOR_STATUS) ++value;

		} else {
			this->lightSensorOutsideAmbientStatus[lightSensor] =
					CSensorValues::AVAILABLE;
			this->lightSensorOutsideAmbient[lightSensor] = value;
		}

		//TODO
		value = 0;

		//check if different value
		if (value != this->lightSensorOutsideShade[lightSensor]) {
			updated = true;
		}

		if (value < 1) {
			this->lightSensorOutsideShade[lightSensor] = 0;
			this->lightSensorOutsideShadeStatus[lightSensor] =
					(SENSOR_STATUS) ++value;

		} else {
			this->lightSensorOutsideShadeStatus[lightSensor] =
					CSensorValues::AVAILABLE;
			this->lightSensorOutsideShade[lightSensor] = value;
		}

		//callback function called if updated
		if (updated && this->lightUpdateFunctionPointers[lightSensor] != NULL) {
			(*lightUpdateFunctionPointers[lightSensor])();
		}
	}

	//humidity
	int humiditySensor = 0;

	for (; humiditySensor < this->humiditySensorConnectedCount;
			humiditySensor++) {
		bool updated = false;

		//TODO
		int value = 0;

		//check if different value
		if (value != this->humiditySensor[humiditySensor]) {
			updated = true;
		}

		if (value < 1) {
			this->humiditySensor[humiditySensor] = 0;
			this->humiditySensorStatus[humiditySensor] =
					(SENSOR_STATUS) ++value;

		} else {
			this->humiditySensorStatus[humiditySensor] =
					CSensorValues::AVAILABLE;
			this->humiditySensor[humiditySensor] = value;
		}

		//callback function called if updated
		if (updated
				&& this->humidityUpdateFunctionPointers[humiditySensor] != NULL) {
			(*humidityUpdateFunctionPointers[humiditySensor])();
		}
	}

	//get values of sensor connected to other boards connected to RS485
	//light
	for (int i = 0; lightSensor < this->lightSensorCount; lightSensor++, i++) {
		bool updated = false;
		int value = this->myRS485IO->getLightSensorInsideAmbientValue(i);

		//check if different value
		if (value != this->lightSensorInsideAmbient[lightSensor]) {
			updated = true;
		}

		if (value < 1) {
			this->lightSensorInsideAmbient[lightSensor] = 0;
			this->lightSensorInsideAmbientStatus[lightSensor] =
					(SENSOR_STATUS) ++value;

		} else {
			this->lightSensorInsideAmbientStatus[lightSensor] =
					CSensorValues::AVAILABLE;
			this->lightSensorInsideAmbient[lightSensor] = value;
		}

		value = this->myRS485IO->getLightSensorOutsideAmbientValue(i);

		//check if different value
		if (value != this->lightSensorOutsideAmbient[lightSensor]) {
			updated = true;
		}

		if (value < 1) {
			this->lightSensorOutsideAmbient[lightSensor] = 0;
			this->lightSensorOutsideAmbientStatus[lightSensor] =
					(SENSOR_STATUS) ++value;

		} else {
			this->lightSensorOutsideAmbientStatus[lightSensor] =
					CSensorValues::AVAILABLE;
			this->lightSensorOutsideAmbient[lightSensor] = value;
		}

		value = this->myRS485IO->getLightSensorOutsideShadeValue(i);

		//check if different value
		if (value != this->lightSensorOutsideShade[lightSensor]) {
			updated = true;
		}

		if (value < 1) {
			this->lightSensorOutsideShade[lightSensor] = 0;
			this->lightSensorOutsideShadeStatus[lightSensor] =
					(SENSOR_STATUS) ++value;

		} else {
			this->lightSensorOutsideShadeStatus[lightSensor] =
					CSensorValues::AVAILABLE;
			this->lightSensorOutsideShade[lightSensor] = value;
		}

		//callback function called if updated
		if (updated && this->lightUpdateFunctionPointers[lightSensor] != NULL) {
			(*lightUpdateFunctionPointers[lightSensor])();
		}
	}

	//humidity
	for (int i = 0; humiditySensor < this->humiditySensorCount;
			humiditySensor++, i++) {
		bool updated = false;
		int value = this->myRS485IO->getHumiditySensorValue(i);

		//check if different value
		if (value != this->humiditySensor[humiditySensor]) {
			updated = true;
		}

		if (value < 1) {
			this->humiditySensor[humiditySensor] = 0;
			this->humiditySensorStatus[humiditySensor] =
					(SENSOR_STATUS) ++value;

		} else {
			this->humiditySensorStatus[humiditySensor] =
					CSensorValues::AVAILABLE;
			this->humiditySensor[humiditySensor] = value;
		}

		//callback function called if updated
		if (updated
				&& this->humidityUpdateFunctionPointers[humiditySensor] != NULL) {
			(*humidityUpdateFunctionPointers[humiditySensor])();
		}
	}

}

//getter for the inside ambient sensor
int CSensorValues::getInsideAmbientSensorValue(int sensor) {
	//check if valid sensor
	if (sensor >= this->lightSensorCount) {
		return -1;
	}

	//if not valid sensor
	if (this->lightSensorInsideAmbientStatus[sensor]
			!= CSensorValues::AVAILABLE) {
		return -1;
	}

	return lightSensorInsideAmbient[sensor];
}


//get the value of the outside ambient sensor
int CSensorValues::getOutsideAmbientSensorValue(int sensor) {
	//check if valid sensor
	if (sensor >= this->lightSensorCount) {
		return -1;
	}

	//if not valid sensor
	if (this->lightSensorOutsideAmbientStatus[sensor]
			!= CSensorValues::AVAILABLE) {
		return -1;
	}

	return lightSensorOutsideAmbient[sensor];
}

//check the value of the sensor under the shade
int CSensorValues::getOutsideShadeSensorValue(int sensor) {
	//check if valid sensor
	if (sensor >= this->lightSensorCount) {
		return -1;
	}

	//if not valid sensor
	if (this->lightSensorOutsideShadeStatus[sensor]
			!= CSensorValues::AVAILABLE) {
		return -1;
	}

	return lightSensorOutsideShade[sensor];
}

//get the value of the humidity sensor
int CSensorValues::getHumiditySensorValue(int sensor) {
	//check if valid sensor
	if (sensor >= this->humiditySensorCount) {
		return -1;
	}

	//if not valid sensor
	if (this->humiditySensorStatus[sensor] != CSensorValues::AVAILABLE) {
		return -1;
	}

	return humiditySensor[sensor];
}

//set a function pointer for a light values
void CSensorValues::setLightFunctionPointer(int sensor,
		voidFuncPointer function) {
	//check if valid sensor
	if (sensor >= this->lightSensorCount) {
		return;
	}

	this->lightUpdateFunctionPointers[sensor] = function;
}

//unset light function pointer
void CSensorValues::unsetLightFunctionPointer(int sensor) {
	//check if valid sensor
	if (sensor >= this->lightSensorCount) {
		return;
	}

	this->lightUpdateFunctionPointers[sensor] = NULL;
}

//set a function pointer for a humidity value
void CSensorValues::setHumidityFunctionPointer(int sensor,
		voidFuncPointer function) {
	//check if valid sensor
	if (sensor >= this->humiditySensorCount) {
		return;
	}

	this->humidityUpdateFunctionPointers[sensor] = function;
}

//unset humiditiy function pointer
void CSensorValues::unsetHumidityFunctionPointer(int sensor) {
	//check if valid sensor
	if (sensor >= this->humiditySensorCount) {
		return;
	}

	this->humidityUpdateFunctionPointers[sensor] = NULL;
}
