//playing sound from a SD card

//standard library
#include <SPI.h>
#include <SD.h>

//TMRpcm library (SD wav card to analog)
#include "TMRpcm.h"

//HCSR04 library (ultrsound ranging device)
#include "ultrasound_hcsr04.h"

//constants
int SERIAL_BAUD_RATE = 9600; //debugging

//pin assignement
int PIN_SD_CS = 53; // Pin 53 at Mega board
int PIN_SPEAKER = 11; // Pin to audio amplifier input. 5,6,11,46 on Mega
int PIN_TRIGGER = 2; //ultrasound trigger
int PIN_ECHO = 3; //ultrasound echo

//play sound TMRpcm object
TMRpcm tmrpcm;

//ultrasound object
UltrasoundHCSR04 hcsr04(PIN_TRIGGER, PIN_ECHO);

//setup
void setup()
{
    //opens serial port, sets data rate to 9600 bps, Useful for debugging
    Serial.begin(SERIAL_BAUD_RATE);

	//set chip select pin as output
 	pinMode(PIN_SD_CS, OUTPUT);

	//SD init
  	Serial.println("Initializing SD card...");
  	if (!SD.begin(PIN_SD_CS))
	{
		Serial.println("SD card initialization failed. EXIT PROGRAM.");
	    return;
  	}
  	Serial.println("SD initialization done.");

	//tmrpcm init
	tmrpcm.speakerPin = PIN_SPEAKER;
	tmrpcm.setVolume(6);
}

//main loop
void loop()
{

	double range;

	//play a tone
	// tone(PIN_SPEAKER, 440);
	// delay(500);
	// noTone(PIN_SPEAKER);

	//check if already playing a sound
	if ( !tmrpcm.isPlaying() )
	{
		//get range from ultrasound
		range = hcsr04.getRange();
		Serial.print("range: ");
		Serial.println(range, DEC);
		if ( (0.1 < range) && (range < 0.3) )
		{
			//play sound
			tmrpcm.play("phone.wav");
			//delay(500);
		}

		if ( (0.3 < range) && (range < 0.6) )
		{
			//play sound
			tmrpcm.play("alarm.wav");
			//delay(500);
		}
	}
	else //if playing, just wait a little bit
	{
		delay(500);
	}
}
