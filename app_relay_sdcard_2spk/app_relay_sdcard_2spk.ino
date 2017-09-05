//Noisy Town, testing relays

//standard library
#include <SPI.h>
#include <SD.h>

//TMRpcm library (SD wav card to analog)
#include "TMRpcm.h"

//HCSR04 library (ultrsound ranging device)
//#include "ultrasound_hcsr04.h"

//constants
int SERIAL_BAUD_RATE = 9600; //debugging
int SOUND_DURATION = 500; //the duration of sounds, [ms]
int LOOP_RATE = 2000; //the period to read ulstrasound  range, [ms]

//pin assignement
int PIN_SD_CS = 53; // Pin 53 at Mega board
int PIN_AUDIO_OUT = 11; // Pin to audio amplifier input. 5,6,11,46 on Mega
int PIN_US_TRIGGER = 32; //ultrasound trigger
int PIN_US_ECHO = 33; //ultrasound echo
int PIN_RELAY_1 = 41;
int PIN_RELAY_2 = 42;

//play sound TMRpcm object
TMRpcm tmrpcm;

//ultrasound object
//UltrasoundHCSR04 hcsr04(PIN_US_TRIGGER, PIN_US_ECHO);

//setup
void setup()
{
    //opens serial port, sets data rate to 9600 bps, Useful for debugging
    Serial.begin(SERIAL_BAUD_RATE);

	//set chip select pin as output
 	pinMode(PIN_SD_CS, OUTPUT);

	//set pins to relays as outputs, and switch-off relays
	pinMode(PIN_RELAY_1, OUTPUT);
	pinMode(PIN_RELAY_2, OUTPUT);
	digitalWrite(PIN_RELAY_1, HIGH);
	digitalWrite(PIN_RELAY_2, HIGH);

	//SD init
  	Serial.println("Initializing SD card...");
  	if (!SD.begin(PIN_SD_CS))
	{
		Serial.println("SD card initialization failed. EXIT PROGRAM.");
	    return;
  	}
  	Serial.println("SD initialization done.");

	//tmrpcm init
	tmrpcm.speakerPin = PIN_AUDIO_OUT;
	tmrpcm.setVolume(6);
}

//main loop
void loop()
{

	digitalWrite(PIN_RELAY_1, LOW);
  	tmrpcm.play("phone.wav");
	delay(SOUND_DURATION);
	digitalWrite(PIN_RELAY_1, HIGH);

	digitalWrite(PIN_RELAY_2, LOW);
 	tmrpcm.play("alarm.wav");
   	delay(SOUND_DURATION);
	digitalWrite(PIN_RELAY_2, HIGH);

	//stop tmrpcm
	tmrpcm.disable();

	//adjust loop rate
	delay(LOOP_RATE);
}
