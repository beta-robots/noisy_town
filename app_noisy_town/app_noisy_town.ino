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
int PIN_RELAY_[4]; //will be initialized at init()
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
bool DEBUGGING = false;
int SERIAL_BAUD_RATE = 9600; //debugging
int SOUND_DURATION = 500; //the duration of sounds, [ms]
int LOOP_RATE = 200; //the period to read ulstrasound  range, [ms]
float RANGE_THRESHOLD_1 = 0.1;
float RANGE_THRESHOLD_2 = 0.4;
float RANGE_THRESHOLD_3 = 0.8;

//play sound TMRpcm object
TMRpcm tmrpcm;

//ultrasound objects
UltrasoundHCSR04 us_1(PIN_US_TRIGGER_1, PIN_US_ECHO_1);
UltrasoundHCSR04 us_2(PIN_US_TRIGGER_2, PIN_US_ECHO_2);
UltrasoundHCSR04 us_3(PIN_US_TRIGGER_3, PIN_US_ECHO_3);
UltrasoundHCSR04 us_4(PIN_US_TRIGGER_4, PIN_US_ECHO_4);

//ranges
//float range_1, range_2, range_3, range_4;
float ranges_[4];
int status; //status <0 means some error

//wav filename
String wavfile_;

//setup
void setup()
{
	//local variables
	int ii;

	// reset status
	status = 0;

    //opens serial port, sets data rate to 9600 bps, Useful for debugging
    Serial.begin(SERIAL_BAUD_RATE);

	//set chip select pin as output
 	pinMode(PIN_SD_CS, OUTPUT);

	//set pins to relays as outputs
	PIN_RELAY_[0] = PIN_RELAY_1;
	PIN_RELAY_[1] = PIN_RELAY_2;
	PIN_RELAY_[2] = PIN_RELAY_3;
	PIN_RELAY_[3] = PIN_RELAY_4;
	for (ii=0; ii<4; ii++)
	{
		pinMode(PIN_RELAY_[ii], OUTPUT);
	}

	//switch-off relays
	for (ii=0; ii<4; ii++)
	{
		digitalWrite(PIN_RELAY_[ii], HIGH);
	}

	//SD init
  	Serial.println("Initializing SD card...");
  	if (!SD.begin(PIN_SD_CS))
	{
		Serial.println("SD card initialization failed. EXIT PROGRAM.");
		status = -1;
	    return;
  	}
	else
	{
		status = 1;
	  	Serial.println("SD initialization done.");
	}

	//tmrpcm init
	tmrpcm.speakerPin = PIN_AUDIO_OUT;
	tmrpcm.setVolume(6);

	//adevrtise success
	toneSuccess();
}

void toneSuccess()
{
	digitalWrite(PIN_RELAY_[0], LOW);
	tone(PIN_AUDIO_OUT, 261); //play a tone
	delay(500); //relax for a while
	digitalWrite(PIN_RELAY_[0], HIGH);
	digitalWrite(PIN_RELAY_[1], LOW);
	tone(PIN_AUDIO_OUT, 330); //play a tone
	delay(500); //relax for a while
	digitalWrite(PIN_RELAY_[1], HIGH);
	digitalWrite(PIN_RELAY_[2], LOW);
	tone(PIN_AUDIO_OUT, 392); //play a tone
	delay(500); //relax for a while
	digitalWrite(PIN_RELAY_[2], HIGH);
	digitalWrite(PIN_RELAY_[3], LOW);
	tone(PIN_AUDIO_OUT, 522); //play a tone
	delay(500); //relax for a while
	digitalWrite(PIN_RELAY_[3], HIGH);
	noTone(PIN_AUDIO_OUT); //mute again

}

void toneWarning()
{
	digitalWrite(PIN_RELAY_[0], LOW);
	tone(PIN_AUDIO_OUT, 440); //play a tone
	delay(300); //relax for a while
	noTone(PIN_AUDIO_OUT); //mute again
	digitalWrite(PIN_RELAY_[0], HIGH);
	delay(1000); //relax for a while
}

void getRanges()
{
	//get range from ultrasounds
	ranges_[0] = us_1.getRange();
	ranges_[1] = us_2.getRange();
	ranges_[2] = us_3.getRange();
	ranges_[3] = us_4.getRange();

	//print range (debugging)
	int ii;
	if (DEBUGGING)
	{
		for (ii=0; ii<4; ii++)
		{
			Serial.print("ranges_[");
			Serial.print(ii, DEC);
			Serial.print("]: ");
			Serial.println(ranges_[ii], DEC);
		}
	}
}

void playSounds()
{
	int ii, jj;
	char c_string[9];
	jj = int(random(0,4)); //this randomize the executed sound in case of multiple ranges are within the zones 1 or 2
	if (DEBUGGING)
	{
		Serial.print("random:  "); Serial.println(jj, DEC);
	}

	//loop checking each range and playing sound accordingly
	for (ii=0; ii<4; ii++)
	{
		//check first zone
		if ( (RANGE_THRESHOLD_1 < ranges_[jj]) && (ranges_[jj] < RANGE_THRESHOLD_2) )
		{
			digitalWrite(PIN_RELAY_[jj], LOW);
			wavfile_ = "T" + String(jj+1) + "001.wav";
			wavfile_.toCharArray(c_string, 10);
			Serial.print("Playing "); Serial.println(c_string);
			tmrpcm.play(c_string); //play sound
			break;
		}

		//check second zone
		if ( (RANGE_THRESHOLD_2 < ranges_[jj]) && (ranges_[jj] < RANGE_THRESHOLD_3) )
		{
			digitalWrite(PIN_RELAY_[jj], LOW);
			wavfile_ = "T" + String(jj+1) + "002.wav";
			wavfile_.toCharArray(c_string, 10);
			Serial.print("Playing "); Serial.println(c_string);
			tmrpcm.play(c_string); //play sound
			break;
		}

		//increment jj
		jj = (jj+1)%4;
	}

	//delay for a while and then switch off relays
	if ( tmrpcm.isPlaying() )
	{
		delay(SOUND_DURATION); //let sound exhibit
		tmrpcm.disable();
		for (ii=0; ii<4; ii++)
		{
			digitalWrite(PIN_RELAY_[ii], HIGH);
		}
	}
	else
	{
		delay(LOOP_RATE); //adjust loop rate
	}

}

//main loop
void loop()
{
	switch (status)
 	{
		case -1:
			toneWarning();
			break;

		case 1:
		default:
			getRanges();
			playSounds();
			break;
	}
}
