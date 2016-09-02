#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <TimeLib.h>
#include <Wire.h>
#include "Header/I2C_Anything.h"

const byte SlaveDeviceId = 1;
byte LastMasterCommand = 0;

void receiveCommand(int howMany){
  LastMasterCommand = Wire.read(); // 1 byte (maximum 256 commands)
}


void slavesRespond(){

  int returnValue = 0;

  switch(LastMasterCommand){
    case 0:   // No new command was received
      Wire.write("NA");
    break;

    case 1:   // Return X sensor value
      returnValue = now();
    break;

    case 2:   // Return Y sensor value
      returnValue = now();
    break;

  }

  unsigned long int ntime = now();
  Serial.println(ntime);
  byte buffer[4];                 // split int value into two bytes buffer
  // convert from an unsigned long int to a 4-byte array
  buffer[0] = (int)((ntime >> 24) & 0xFF) ;
  buffer[1] = (int)((ntime >> 16) & 0xFF) ;
  buffer[2] = (int)((ntime >> 8) & 0XFF);
  buffer[3] = (int)((ntime & 0XFF));
  Serial.println(buffer[0]);
  		Serial.println(buffer[1]);
  		Serial.println(buffer[2]);
  		Serial.println(buffer[3]);
  Wire.write(buffer, 4);          // return response to last command
  LastMasterCommand = 0;          // null last Master's command
}



// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

unsigned int localPort = 8888;      // local port to listen for UDP packets

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

//address of the slave
int wireAddress = 2;

//Used to store the NTP time
unsigned long secsSince1900;

//used for the wire protocol to store the last command from the master
byte lastCommand = 0;

// used for two output pins to show the working transmit/receive function
int receiveLED = 6;
int requestLED = 7;

//define the pins with the sensors
int tempSensor = A0;
int lightSensor = A1;
int humiditySensor = A2;
int humidityLimitSensor = 8;

//define the variables for the sensor values
int temprature = 0;
int lightValue = 0;
int humidity = 0;
int humidityLimit = 0;

IPAddress timeServer(195, 145, 119, 188); // time-a.timefreq.bldrdoc.gov NTP server
// IPAddress timeServer(132, 163, 4, 102); // time-b.timefreq.bldrdoc.gov NTP server
// IPAddress timeServer(132, 163, 4, 103); // time-c.timefreq.bldrdoc.gov NTP server

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

const int syncInterval = 3600;
const int timeZone = 1;     // Central European Time
//const int timeZone = -5;  // Eastern Standard Time (USA)
//const int timeZone = -4;  // Eastern Daylight Time (USA)
//const int timeZone = -8;  // Pacific Standard Time (USA)
//const int timeZone = -7;  // Pacific Daylight Time (USA)

time_t prevDisplay = 0; // when the digital clock was displayed




int adjustDstEurope()
{
 // last sunday of march
 int beginDSTDate=  (31 - (5* year() /4 + 4) % 7);
 Serial.println(beginDSTDate);
 int beginDSTMonth=3;
 //last sunday of october
 int endDSTDate= (31 - (5 * year() /4 + 1) % 7);
 Serial.println(endDSTDate);
 int endDSTMonth=10;
 // DST is valid as:
 if (((month() > beginDSTMonth) && (month() < endDSTMonth))
     || ((month() == beginDSTMonth) && (day() >= beginDSTDate))
     || ((month() == endDSTMonth) && (day() <= endDSTDate)))
 return 7200;  // DST europe = utc +2 hour
 else return 3600; // nonDST europe = utc +1 hour
}



//Used for the I2C Communiction between master and slave
//executed when data is received from the master -> used mainly to determine what the master will call for next
void receiveEventFromWire(int howMany) {
	lastCommand = Wire.read();
}

//executed when data requested by master -> what is sent back is determined via the last received command by the master
void requestEventFromWire() {

 unsigned long int ntime = now() + adjustDstEurope();

	switch (lastCommand) {
	case 0:    //Temperature was called
		I2C_singleWriteAnything(temprature);
		break;
	case 1: //light value was called
		I2C_singleWriteAnything(lightValue);
		break;
	case 2:  //humidity was called
		I2C_singleWriteAnything(humidity);
		break;
	case 3: // humidity limit was called
		I2C_singleWriteAnything(humidityLimit);
		break;
	case 4: // time was called

		  Serial.println(ntime);
		  byte buffer[4];                 // split int value into two bytes buffer
		  // convert from an unsigned long int to a 4-byte array
		  buffer[0] = (int)((ntime >> 24) & 0xFF) ;
		  buffer[1] = (int)((ntime >> 16) & 0xFF) ;
		  buffer[2] = (int)((ntime >> 8) & 0XFF);
		  buffer[3] = (int)((ntime & 0XFF));

		  Serial.println(buffer[0]);
		  		Serial.println(buffer[1]);
		  		Serial.println(buffer[2]);
		  		Serial.println(buffer[3]);

		  Wire.write(buffer, 4);          // return response to last command


		break;
	default:
		int def = -1;
		I2C_singleWriteAnything(def);
		break;
	}

	lastCommand = 0;          // null last Master's command

}


// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address) {
	// set all bytes in the buffer to 0
	memset(packetBuffer, 0, NTP_PACKET_SIZE);
	// Initialize values needed to form NTP request
	// (see URL above for details on the packets)
	packetBuffer[0] = 0b11100011;   // LI, Version, Mode
	packetBuffer[1] = 0;     // Stratum, or type of clock
	packetBuffer[2] = 6;     // Polling Interval
	packetBuffer[3] = 0xEC;  // Peer Clock Precision
	// 8 bytes of zero for Root Delay & Root Dispersion
	packetBuffer[12] = 49;
	packetBuffer[13] = 0x4E;
	packetBuffer[14] = 49;
	packetBuffer[15] = 52;

	// all NTP fields have been given values, now
	// you can send a packet requesting a timestamp:
	Udp.beginPacket(address, 123); //NTP requests are to port 123
	Udp.write(packetBuffer, NTP_PACKET_SIZE);
	Udp.endPacket();
	return 0;
}


time_t getNtpTime() {
	(Udp.parsePacket() > 0); // discard any previously received packets
	Serial.println("Transmit NTP Request");

	int count = 0;

	while (count < 40) {

		sendNTPpacket(timeServer); // send an NTP packet to a time server

		Serial.print("Try to find NTP response:");
		Serial.println(count);
		delay(5000);
		if (Udp.parsePacket()) {
			// We've received a packet, read the data from it
			Udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

			// convert four bytes starting at location 40 to a long integer
			secsSince1900 = (unsigned long) packetBuffer[40] << 24;
			secsSince1900 |= (unsigned long) packetBuffer[41] << 16;
			secsSince1900 |= (unsigned long) packetBuffer[42] << 8;
			secsSince1900 |= (unsigned long) packetBuffer[43];

			//the timestamp starts at byte 40 of the received packet and is four bytes,
			// or two words, long. First, esxtract the two words:
			unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
			unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
			// combine the four bytes (two words) into a long integer
			// this is NTP time (seconds since Jan 1 1900):
			Serial.print("Seconds since Jan 1 1900 = ");
			Serial.println(secsSince1900);

			// now convert NTP time into everyday time:
			Serial.print("Unix time = ");
			// Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
			const unsigned long seventyYears = 2208988800UL;
			// subtract seventy years:
			unsigned long epoch = secsSince1900 - seventyYears;
			// print Unix time:
			Serial.println(epoch);

			// print the hour, minute and second:
			Serial.print("The UTC time is "); // UTC is the time at Greenwich Meridian (GMT)
			Serial.print((epoch % 86400L) / 3600); // print the hour (86400 equals secs per day)
			Serial.print(':');
			if (((epoch % 3600) / 60) < 10) {
				// In the first 10 minutes of each hour, we'll want a leading '0'
				Serial.print('0');
			}
			Serial.print((epoch % 3600) / 60); // print the minute (3600 equals secs per minute)
			Serial.print(':');
			if ((epoch % 60) < 10) {
				// In the first 10 seconds of each minute, we'll want a leading '0'
				Serial.print('0');
			}
			Serial.println(epoch % 60); // print the second

			return epoch +6 ; // adjustment for inaccuracies
		}
		count++;
	}

	Serial.println("No NTP Response :-(");
	return 0; // return 0 if unable to get the time

}



void setup() {
	//set the start values for the LEDs
	pinMode(receiveLED, OUTPUT);
	pinMode(requestLED, OUTPUT);
	digitalWrite(receiveLED, LOW);
	digitalWrite(requestLED, LOW);

	//declare the digital Input
	pinMode(humidityLimitSensor, INPUT);

	// Open serial communications and wait for port to open:
	Serial.begin(9600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for Leonardo only
	}

	delay(250);
	Serial.println("Setup");
	// start Ethernet and UDP
	if (Ethernet.begin(mac) == 0) {
		// no point in carrying on, so do nothing forevermore:
		while (1) {
			Serial.println("Failed to configure Ethernet using DHCP");
			delay(10000);
		}
	}
	Serial.print("IP number assigned by DHCP is ");
	Serial.println(Ethernet.localIP());
	Udp.begin(localPort);

	server.begin();

	setSyncInterval(syncInterval);
	setSyncProvider(getNtpTime);


//	Wire.begin(SlaveDeviceId);      // join i2c bus with Slave ID
//	  Wire.onReceive(receiveCommand); // register talk event
//	  Wire.onRequest(slavesRespond);  // register callback event



	Wire.begin(wireAddress);
	Wire.onRequest(requestEventFromWire);
	Wire.onReceive(receiveEventFromWire);
}

void loop() {

	readSensors();
	if (timeStatus() != timeNotSet) {


		if (now() != prevDisplay) { //update the display only if time has changed
prevDisplay = now();
			digitalClockDisplay();
			Serial.print("Now(): ");
	Serial.print(now());
	Serial.println();
		}
	}

}

void readSensors() {
	temprature = analogRead(tempSensor);
	lightValue = analogRead(lightSensor);
	humidity = analogRead(humiditySensor);
	humidityLimit = digitalRead(humidityLimitSensor);

}



// Used to show a web page for the user

void serverProcedure() {

	// listen for incoming clients
	EthernetClient client = server.available();
	if (client) {
		Serial.println("new client");
		// an http request ends with a blank line
		boolean currentLineIsBlank = true;
		while (client.connected()) {
			if (client.available()) {
				char c = client.read();
				Serial.write(c);
				// if you've gotten to the end of the line (received a newline
				// character) and the line is blank, the http request has ended,
				// so you can send a reply
				if (c == '\n' && currentLineIsBlank) {
					// send a standard http response header
					client.println("HTTP/1.1 200 OK");
					client.println("Content-Type: text/html");
					client.println("Connection: close"); // the connection will be closed after completion of the response
					client.println("Refresh: 5"); // refresh the page automatically every 5 sec
					client.println();
					client.println("<!DOCTYPE HTML>");
					client.println("<html>");
					// output the value of each analog input pin
					for (int analogChannel = 0; analogChannel < 6;
							analogChannel++) {
						int sensorReading = analogRead(analogChannel);
						client.print("analog input ");
						client.print(analogChannel);
						client.print(" is ");
						client.print(sensorReading);
						client.println("<br />");
					}
					client.println("</html>");
					break;
				}
				if (c == '\n') {
					// you're starting a new line
					currentLineIsBlank = true;
				} else if (c != '\r') {
					// you've gotten a character on the current line
					currentLineIsBlank = false;
				}
			}
		}
		// give the web browser time to receive the data
		delay(1);
		// close the connection:
		client.stop();
		Serial.println("client disonnected");
	}
}

void printDigits(int digits) {
	// utility for digital clock display: prints preceding colon and leading 0
	Serial.print(":");
	if (digits < 10)
		Serial.print('0');
	Serial.print(digits);
}

//shows the digital clock via the serial interface

void digitalClockDisplay() {
	// digital clock display of the time
	Serial.print(hour());
	printDigits(minute());
	printDigits(second());
	Serial.print(" ");
	Serial.print(day());
	Serial.print(" ");
	Serial.print(month());
	Serial.print(" ");
	Serial.print(year());
	Serial.println();
}

//-------- NTP code ----------



