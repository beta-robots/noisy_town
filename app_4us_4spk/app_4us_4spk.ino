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

//pin assignment speakers
int PIN_SPEAKER_1 = 6; // Pin to audio amplifier input. 5,6,11,46 on Mega
int PIN_SPEAKER_2 = 11;
int PIN_SPEAKER_3 = 46;

//pin assignment ultrasound
int PIN_TRIGGER1 = 32;  //first  ultrasound trigger
int PIN_ECHO1 = 33;     //first  ultrasound echo
int PIN_TRIGGER2 = 34;  //second ultrasound trigger
int PIN_ECHO2 = 35;     //second ultrasound echo
int PIN_TRIGGER3 = 36;  //third  ultrasound trigger
int PIN_ECHO3 = 37;     //third  ultrasound echo

//play sound TMRpcm object
TMRpcm tmrpcm_1;
TMRpcm tmrpcm_2;

//ultrasound object
UltrasoundHCSR04 hcsr04_1(PIN_TRIGGER1, PIN_ECHO1);
UltrasoundHCSR04 hcsr04_2(PIN_TRIGGER2, PIN_ECHO2);
UltrasoundHCSR04 hcsr04_3(PIN_TRIGGER3, PIN_ECHO3);

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
	tmrpcm_1.setVolume(3);
  tmrpcm_2.speakerPin = PIN_SPEAKER_2;
  tmrpcm_2.setVolume(3);

  tmrpcm_1.speakerPin2 = PIN_SPEAKER_3;  
}

//main loop
void loop()
{

  double range_1, range_2, range_3;

  if ( !tmrpcm_1.isPlaying()  && !tmrpcm_2.isPlaying())
  {
    //get range from ultrasoun
    range_1 = hcsr04_1.getRange();
    range_2 = hcsr04_2.getRange();
    range_3 = hcsr04_3.getRange();

  
    //print range
    Serial.print("Range_1: ");
    Serial.println(range_1, DEC);
    Serial.print("Range_2: ");
    Serial.println(range_2, DEC);
    Serial.print("Range_3: ");
    Serial.println(range_3, DEC);


  
  
    if ( (0.1 < range_1) && (range_1 < 0.6) ){
      //play sound
      //tmrpcm_1.play("phone.wav");
      tmrpcm_1.play("phone.wav",0);
       tmrpcm_1.play("silence.wav",1);
      delay(750);
    }

    else if ( (0.1 < range_2) && (range_2 < 0.6) ){
      //play sound
      tmrpcm_1.play("silence.wav",0);
      tmrpcm_1.play("alarm.wav",1);
      delay(500);
    }

    else if ( (0.1 < range_3) && (range_3 < 0.6) ){
      //play sound
      tmrpcm_2.play("phone.wav");
      delay(500);
    }
  }
  

  else{
    tmrpcm_1.disable();
    tmrpcm_2.disable();

    delay(100);

    
  }
}
