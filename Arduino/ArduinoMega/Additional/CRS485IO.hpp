/*
 * RS485IO.hpp
 *
 *  Created on: 08.04.2016
 *      Author: Thorsten
 */

#ifndef CRS485IO_HPP_
#define CRS485IO_HPP_

class CRS485IO {
private:

protected:

public:
	CRS485IO();
	~CRS485IO();


	//getter for the sensors
	int getHumiditySensorValue(int sensor);
	int getLightSensorInsideAmbientValue(int sensor);
	int getLightSensorOutsideShadeValue(int sensor);
	int getLightSensorOutsideAmbientValue(int sensor);
};



#endif /* CRS485IO_HPP_ */
