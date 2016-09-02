//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2016-03-31 19:50:57

#include "Arduino.h"
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <TimeLib.h>
#include <Wire.h>
#include "Header/I2C_Anything.h"
void receiveCommand(int howMany);
void slavesRespond();
void receiveEventFromWire(int howMany) ;
void requestEventFromWire() ;
unsigned long sendNTPpacket(IPAddress& address) ;
time_t getNtpTime() ;
void setup() ;
void loop() ;
void readSensors() ;
void serverProcedure() ;
void printDigits(int digits) ;
void digitalClockDisplay() ;

#include "ArduinoUno.ino"

