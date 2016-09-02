/*
 * CStatusFrame.cpp
 *
 *  Created on: 05.04.2016
 *      Author: Thorsten
 */

#include "CStatusFrame.hpp"

CStatusFrame::CStatusFrame(UTFT * tft, UTouch * touch,
		CSystemSetup * systemSetup, CSensorValues * sensorValues) :
		CControlsFrame(tft, touch, 0), mySystemSetup(systemSetup), mySensorValues(
				sensorValues) {

}

CStatusFrame::~CStatusFrame() {

}

void CStatusFrame::display() {
	CControlsFrame::display();
	this->drawSimpleLightPanel(1, FRAMESTART + 1);
	this->drawSimpleShadesPanel(1, 141);
	this->drawSimpleTempPanel(241, FRAMESTART + 1);
	this->drawSimpleHumidityPanel(241, 141);

}

void CStatusFrame::initDisplay() {
	CControlsFrame::initDisplay();
}

void CStatusFrame::updateDisplay() {

}

void CStatusFrame::drawSimpleLightPanel(int x, int y) {
	this->myGLCD->setColor(VGA_BLACK);
	this->myGLCD->drawRoundRect(x, y, 238, 139);

}

void CStatusFrame::drawSimpleShadesPanel(int x, int y) {
	this->myGLCD->setColor(VGA_BLACK);
	this->myGLCD->drawRoundRect(x, y, 238, 238);
}

void CStatusFrame::drawSimpleTempPanel(int x, int y) {
	this->myGLCD->setColor(VGA_BLACK);
	this->myGLCD->drawRoundRect(x, y, 318, 139);
}

void CStatusFrame::drawSimpleHumidityPanel(int x, int y) {
	this->myGLCD->setColor(VGA_BLACK);
	this->myGLCD->drawRoundRect(x, y, 318, 238);
}

void CStatusFrame::drawSingleHumidityIndication(int x, int y) {

}

void CStatusFrame::drawSimpleLightIndication(int x, int y) {

}

void CStatusFrame::drawSimpleShadeIndication(int x, int y) {

}

void CStatusFrame::updateValues() {

}
