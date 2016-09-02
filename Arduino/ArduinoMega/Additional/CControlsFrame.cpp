/*
 * CControlsFrame.cpp
 *
 *  Created on: 25.03.2016
 *      Author: Thorsten
 */

/*
 * CClockGUI.cpp
 *
 *  Created on: 20.03.2016
 *      Author: Thorsten
 */

#include "CControlsFrame.hpp"

extern uint8_t SmallFont[];
extern uint8_t Dingbats1_XL[];

CControlsFrame::CControlsFrame(UTFT *newGLCD, UTouch * newTouch, int active) :
		myGLCD(newGLCD), myTouch(newTouch), displayXSize(newGLCD->disp_x_size), displayYSize(
				newGLCD->disp_y_size), activeButton(active) {
	this->myButtons = new UTFT_Buttons(myGLCD, myTouch);
	this->myButtons->setTextFont(SmallFont);
	this->myButtons->setSymbolFont(Dingbats1_XL);
	this->buttonCount = 5;
	this->framebuttons = new int[buttonCount];
	uint16_t height = 26;
	uint16_t width = 40;

	for (int i = 0; i < this->buttonCount; i++) {

		switch (i) {
		case 0:
			this->framebuttons[i] = this->myButtons->addButton((i * width), 0,
					width, height, (char *) "h", BUTTON_SYMBOL);
			break;
		case 1:
			this->framebuttons[i] = this->myButtons->addButton((i * width), 0,
					width, height, (char *) "9", BUTTON_SYMBOL);
			break;
		case 2:
			this->framebuttons[i] = this->myButtons->addButton((i * width), 0,
					width, height, (char *) "W", BUTTON_SYMBOL);
			break;
		case 3:
			this->framebuttons[i] = this->myButtons->addButton((i * width), 0,
					width, height, (char *) "8", BUTTON_SYMBOL);
			break;
		case 4:
			this->framebuttons[i] = this->myButtons->addButton((i * width), 0,
					width, height, (char *) "w", BUTTON_SYMBOL);
			break;
		default:
			this->framebuttons[i] = this->myButtons->addButton((i * width), 0,
					width, height, (char *) "a", BUTTON_SYMBOL);
			break;
		}
	}
}

void CControlsFrame::initDisplay() {
	this->myGLCD->setBackColor(VGA_WHITE);
	this->myGLCD->setColor(VGA_WHITE);
	this->myGLCD->fillRect(0, 0, 319, 239);
	this->myGLCD->setColor(VGA_GRAY);
	this->myGLCD->setBackColor(VGA_GRAY);
	this->myGLCD->fillRect(0, 0, 319, 26);
}

CControlsFrame::~CControlsFrame() {
	this->myGLCD = NULL;
	this->myTouch = NULL;
}

void CControlsFrame::display() {
	this->myButtons->setButtonColors(VGA_BLACK, VGA_GRAY, VGA_GRAY, VGA_BLACK,
	VGA_SILVER);
	this->myButtons->disableButton(this->framebuttons[this->activeButton], true);
	this->myButtons->drawButtons();

}
