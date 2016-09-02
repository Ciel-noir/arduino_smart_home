/*
 * CSensorsValues.hpp
 *
 *  Created on: 05.04.2016
 *      Author: Thorsten
 */

#ifndef CSENSORVALUES_HPP_
#define CSENSORVALUES_HPP_
#include "CWireIO.hpp"
#include "CRS485IO.hpp"

/*
 * Class holds all the sensor values of the system
 */
class CSensorValues {
public:
	//definition of function pointer to a callback function
	typedef void (*voidFuncPointer)();

	//check if sensor value is available
	enum SENSOR_STATUS {
		INVALID = 0, UNAVAILABLE = 1, AVAILABLE = 2
	};


	//position of the light sensors
	enum LIGHT_SENSOR_POSITION {
		SHADE_LIVING_LEFT = 0,
		SHADE_LIVING_RIGHT = 1,
		SHADE_SLEEP_MAIN = 2,
		SHADE_KITCHEN_MAIN = 3
	};

	//position of the humidity sensors
	enum HUMIDITY_SENSOR_POSITION {
		HUM_LIVING_LEFT = 0,
		HUM_LIVING_RIGHT = 1,
		HUM_KITCHEN_LEFT = 2,
		HUM_KITCHEN_LEFT_MID = 3,
		HUM_KITCHEN_RIGHT_MID = 4,
		HUM_KITCHEN_RIGHT = 5
	};

private:
	//Connection to get values from the wire
	CWireIO * myWireIO;


	//RS485 connection
	CRS485IO * myRS485IO;

	//the count of connected and total sensors
	const int lightSensorCount;
	const int lightSensorConnectedCount;
	const int humiditySensorCount;
	const int humiditySensorConnectedCount;

	//the values of the sensors
	int * lightSensorInsideAmbient;
	int * lightSensorOutsideShade;
	int * lightSensorOutsideAmbient;
	int * humiditySensor;


	//status of the values
	SENSOR_STATUS * lightSensorInsideAmbientStatus;
	SENSOR_STATUS * lightSensorOutsideAmbientStatus;
	SENSOR_STATUS * lightSensorOutsideShadeStatus;
	SENSOR_STATUS * humiditySensorStatus;

	//array of the function pointers
	voidFuncPointer lightUpdateFunctionPointers[];
	voidFuncPointer humidityUpdateFunctionPointers[];

protected:

public:
	//Constructor
	CSensorValues(CWireIO * wire,  CRS485IO * rs485IO);

	//Destructor
	~CSensorValues();

	//updates the sensor values
	void updateValues();

	//getters for the sensor values
	int getInsideAmbientSensorValue(int sensor);
	int getOutsideAmbientSensorValue(int sensor);
	int getOutsideShadeSensorValue(int sensor);
	int getHumiditySensorValue(int sensor);

	//get the shade status
	int getShadePosition(int shade);

	//function pointers to update functions for one update function each
	void setLightFunctionPointer(int sensor, voidFuncPointer function);
	void unsetLightFunctionPointer(int sensor);
	void setHumidityFunctionPointer(int sensor, voidFuncPointer function);
	void unsetHumidityFunctionPointer(int sensor);
};

#endif /* CSENSORVALUES_HPP_ */
