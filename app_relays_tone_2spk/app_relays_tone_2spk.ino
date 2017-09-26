//Noisy Town, testing relays

//constants
int SERIAL_BAUD_RATE = 9600; //debugging
int SOUND_DURATION = 500; //the duration of sounds, [ms]
int LOOP_RATE = 2000; //the period to read ulstrasound  range, [ms]

//pin assignement
int PIN_AUDIO_OUT = 11; // Pin to audio amplifier input. 5,6,11,46 on Mega
int PIN_RELAY_1 = 44;
int PIN_RELAY_2 = 45;

//setup
void setup()
{
    //opens serial port, sets data rate to 9600 bps, Useful for debugging
    Serial.begin(SERIAL_BAUD_RATE);

	//set pins to relays as outputs
    pinMode(PIN_RELAY_1, OUTPUT);
    pinMode(PIN_RELAY_2, OUTPUT);
}

//main loop
void loop()
{

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
}
