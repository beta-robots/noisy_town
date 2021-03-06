//playing sound from a SD card
/* SD reader
 *    CS  --- 53
 *    D1  --- 51
 *    VCC --- 5V
 *    SCK --- 52
 *    GND --- GND
 *    DO  --- 50
 * Ultrasound
 *    VCC --- 5V
 *    Trig -- 32
 *    Echo -- 33
 *    GND --- GND
 * Amplifier
 *    10uF -- 11 
 */
//standard library
#include <SPI.h>
#include <SD.h>

//TMRpcm library (SD wav card to analog)
#include "TMRpcm.h"

//HCSR04 library (ultrsound ranging device)
#include "ultrasound_hcsr04.h"

//constants
int SERIAL_BAUD_RATE = 9600; //debugging
int SOUND_DURATION = 500; //the duration of sounds, [ms]
int LOOP_RATE = 2000; //the period to read ulstrasound  range, [ms]

//pin assignement
int PIN_SD_CS = 53; // Pin 53 at Mega board
int PIN_SPEAKER = 11; // Pin to audio amplifier input. 5,6,11,46 on Mega
int PIN_TRIGGER = 32; //ultrasound trigger
int PIN_ECHO = 33; //ultrasound echo

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
     //pinMode(PIN_SPEAKER, OUTPUT);

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
  tone(PIN_SPEAKER, 440);
	delay(500);
	noTone(PIN_SPEAKER);
  //tmrpcm.disable();
  delay(2000);

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
