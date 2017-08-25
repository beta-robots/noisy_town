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

//pin assignement
int PIN_SD_CS = 53; // Pin 53 at Mega board
int PIN_SPEAKER_1 = 5; // Pin to audio amplifier input. 5,6,11,46 on Mega
int PIN_SPEAKER_2 = 6;
int PIN_SPEAKER_3 = 11;
int PIN_SPEAKER_4 = 46;
int PIN_TRIGGER = 32; //ultrasound trigger
int PIN_ECHO = 33; //ultrasound echo

//play sound TMRpcm object
TMRpcm tmrpcm_1;
TMRpcm tmrpcm_2;
TMRpcm tmrpcm_3;
TMRpcm tmrpcm_4;

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
	tmrpcm_1.speakerPin = PIN_SPEAKER_1;
	tmrpcm_1.setVolume(6);
  tmrpcm_2.speakerPin = PIN_SPEAKER_2;
  tmrpcm_2.setVolume(6);
  tmrpcm_3.speakerPin = PIN_SPEAKER_3;
  tmrpcm_3.setVolume(6);
  tmrpcm_4.speakerPin = PIN_SPEAKER_4;
  tmrpcm_4.setVolume(6);

  tmrpcm_2.speakerPin2 = 46;  
  tmrpcm_3.speakerPin2 = 46;
}

//main loop
void loop()
{

  double range;

  if ( !tmrpcm_1.isPlaying() )
  {
    //get range from ultrasoun
    range = hcsr04.getRange();
  
    //print range
    Serial.print("Range: ");
    Serial.println(range, DEC);

  
  
    if ( (0.1 < range) && (range < 0.6) ){
      //play sound
      //tmrpcm_1.play("phone.wav");
      tmrpcm_2.play("phone.wav",0);
      tmrpcm_2.play("alarm.wav",1);
      tmrpcm_3.play("phone.wav",0);
      tmrpcm_3.play("alarm.wav",1);
      //tmrpcm_4.play("phone.wav");
      Serial.println("playing");
      delay(750);
    }
  
  }

  else{
    tmrpcm_1.disable();
    tmrpcm_2.disable();
    tmrpcm_3.disable();
    tmrpcm_4.disable();
    delay(100);
   // noTone(PIN_SPEAKER);
    
  }
}
