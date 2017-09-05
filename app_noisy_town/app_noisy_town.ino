//Noisy Town, testing relays

//standard library
#include <SPI.h>
#include <SD.h>

//TMRpcm library (SD wav card to analog)
#include "TMRpcm.h"

//HCSR04 library (ultrsound ranging device)
#include "ultrasound_hcsr04.h"

//pin assignement
int PIN_SD_CS = 53; // Pin 53 at Mega board
int PIN_AUDIO_OUT = 11; // Pin to audio amplifier input. 5,6,11,46 on Mega
int PIN_RELAY_1 = 42; //to relay 1
int PIN_RELAY_2 = 43; //to relay 2
int PIN_RELAY_3 = 44; //to relay 3
int PIN_RELAY_4 = 45; //to relay 4
int PIN_US_TRIGGER_1 = 30; //ultrasound trigger 1
int PIN_US_ECHO_1 = 31; //ultrasound echo 1
int PIN_US_TRIGGER_2 = 32; //ultrasound trigger 2
int PIN_US_ECHO_2 = 33; //ultrasound echo 2
int PIN_US_TRIGGER_3 = 34; //ultrasound trigger 3
int PIN_US_ECHO_3 = 35; //ultrasound echo 3
int PIN_US_TRIGGER_4 = 36; //ultrasound trigger 4
int PIN_US_ECHO_4 = 37; //ultrasound echo 4

//constants
int SERIAL_BAUD_RATE = 9600; //debugging
int SOUND_DURATION = 500; //the duration of sounds, [ms]
int LOOP_RATE = 200; //the period to read ulstrasound  range, [ms]

//play sound TMRpcm object
TMRpcm tmrpcm;

//ultrasound objects
UltrasoundHCSR04 us_1(PIN_US_TRIGGER_1, PIN_US_ECHO_1);
UltrasoundHCSR04 us_2(PIN_US_TRIGGER_2, PIN_US_ECHO_2);
UltrasoundHCSR04 us_3(PIN_US_TRIGGER_3, PIN_US_ECHO_3);
UltrasoundHCSR04 us_4(PIN_US_TRIGGER_4, PIN_US_ECHO_4);

//setup
void setup()
{
    //opens serial port, sets data rate to 9600 bps, Useful for debugging
    Serial.begin(SERIAL_BAUD_RATE);

	//set chip select pin as output
 	pinMode(PIN_SD_CS, OUTPUT);

	//set pins to relays as outputs
	pinMode(PIN_RELAY_1, OUTPUT);
	pinMode(PIN_RELAY_2, OUTPUT);
	pinMode(PIN_RELAY_3, OUTPUT);
	pinMode(PIN_RELAY_4, OUTPUT);

	//switch-off relays
	digitalWrite(PIN_RELAY_1, HIGH);
	digitalWrite(PIN_RELAY_2, HIGH);
	digitalWrite(PIN_RELAY_3, HIGH);
	digitalWrite(PIN_RELAY_4, HIGH);

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
	double range_1, range_2, range_3, range_4;

	//get range from ultrasounds
    range_1 = us_1.getRange();
    range_2 = us_2.getRange();
    range_3 = us_3.getRange();
	range_4 = us_4.getRange();

    //print range (debugging)
    Serial.print("range_1: "); Serial.println(range_1, DEC);
    Serial.print("range_2: "); Serial.println(range_2, DEC);
    Serial.print("range_3: "); Serial.println(range_3, DEC);
	Serial.print("range_4: "); Serial.println(range_4, DEC);

	//check ranges
	if ( (0.1 < range_1) && (range_1 < 0.6) )
	{
		digitalWrite(PIN_RELAY_1, LOW);
		tmrpcm.play("alarm.wav"); //play sound
	}

	//loop control
	if ( tmrpcm.isPlaying() )
	{
		delay(SOUND_DURATION); //let sound exhibit
		digitalWrite(PIN_RELAY_1, HIGH);
		digitalWrite(PIN_RELAY_2, HIGH);
		digitalWrite(PIN_RELAY_3, HIGH);
		digitalWrite(PIN_RELAY_4, HIGH);
	}
	else
	{
		delay(LOOP_RATE); //adjust loop rate
	}
}
