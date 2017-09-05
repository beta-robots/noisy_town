//Noisy Town, testing relays

//standard library
//#include <SPI.h>
//#include <SD.h>

//TMRpcm library (SD wav card to analog)
//#include "TMRpcm.h"

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
//TMRpcm tmrpcm;

//ultrasound object
//UltrasoundHCSR04 hcsr04(PIN_US_TRIGGER, PIN_US_ECHO);

//setup
void setup()
{
    //opens serial port, sets data rate to 9600 bps, Useful for debugging
    Serial.begin(SERIAL_BAUD_RATE);

	//set chip select pin as output
 	//pinMode(PIN_SD_CS, OUTPUT);

	//set pins to relays as outputs
        pinMode(PIN_RELAY_1, OUTPUT);
        pinMode(PIN_RELAY_2, OUTPUT);
        
	//SD init
	/*
  	Serial.println("Initializing SD card...");
  	if (!SD.begin(PIN_SD_CS))
	{
		Serial.println("SD card initialization failed. EXIT PROGRAM.");
	    return;
  	}
  	Serial.println("SD initialization done.");
	*/

	//tmrpcm init
	//tmrpcm.speakerPin = PIN_AUDIO_OUT;
	//tmrpcm.setVolume(6);
}

//main loop
void loop()
{

	double range;

	//play a tone
	digitalWrite(PIN_RELAY_1, LOW);
  	tone(PIN_AUDIO_OUT, 440);
	delay(SOUND_DURATION);
	noTone(PIN_AUDIO_OUT);
	digitalWrite(PIN_RELAY_1, HIGH);

	digitalWrite(PIN_RELAY_2, LOW);
  	tone(PIN_AUDIO_OUT, 880);
	delay(SOUND_DURATION);
	noTone(PIN_AUDIO_OUT);
	digitalWrite(PIN_RELAY_2, HIGH);

  	delay(LOOP_RATE);

        //get range from ultrasound
/*	range = hcsr04.getRange();
	Serial.print("range: ");
	Serial.println(range, DEC);

	//check range limits and play sound accordingly
	if ( (0.1 < range) && (range < 0.2) )
	{
	  tmrpcm.play("phone.wav");
          delay(SOUND_DURATION);
	}
	if ( (0.2 < range) && (range < 0.3) )
	{
	  tmrpcm.play("alarm.wav");
	  delay(SOUND_DURATION);
	}

 tmrpcm.play("alarm.wav");
   delay(SOUND_DURATION);

	//silence
	//noTone(PIN_SPEAKER);
	tmrpcm.disable();

	//adjust loop rate
	delay(LOOP_RATE);
*/
}
