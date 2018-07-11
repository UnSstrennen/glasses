/*
Devices:
#1 - left side distance (sonic)
#2 - center distance (sonic)
#3 - right side distance (sonic)

if you request more than 1 byte from IIC line, use [while (Wire.available())]
*/

#include <SoftwareSerial.h>
#include <Wire.h>
#include <DFRobotDFPlayerMini.h>

const byte RX = 10;
const byte TX = 11;

SoftwareSerial music_player(RX, TX);

DFRobotDFPlayerMini myDFPlayer;

byte L, C, R;

//-----
const byte volumeDecrease = 5; //decreased general volume
//-----

void setup() 
{
  Serial.begin(9600);  // start serial for output
  player_settings();
  Wire.begin();        // join i2c bus (address optional for master)
}

void loop() 
{
/* Requesting bytes from slave devices */
// slave may send less than requested, so using -> 'while()'

	Wire.requestFrom(1, 1);    // requesting byte from device #1
	L = Wire.read(); // receive byte as character
	Serial.println(L);         // print the character
	L = map (c, 0, 170, 30, 0);

	Wire.requestFrom(2, 1);    // requesting byte from device #2
	C = Wire.read(); // receive a byte as character
	Serial.println(C);         // print the character
	C = map (c, 0, 170, 30, 0);

	Wire.requestFrom(3, 1);    // requesting byte from device #3
	R = Wire.read(); // receive a byte as character
	Serial.println(R);         // print the character
	R = map (c, 0, 170, 30, 0);


/* Playing Sounds */

	playSound(1, L - volumeDecrease); // Left side track
	playSound(3, C - volumeDecrease); // Center track
	playSound(5, R - volumeDecrease); // Right side track
}

void playSound(byte TRACK_NUMBER, byte volume) 
{ // playing track 'TRACK_NUMBER' with volume 'volume'
	myDFPlayer.volume(volume);
	myDFPlayer.play(TRACK_NUMBER);
}

void player_settings() 
{
	music_player.begin (9600); // opening soft-port
		
	Serial.println(F("\nInitializing DFPlayer\nThis operation may take some time . . ."));

	if (!myDFPlayer.begin(music_player)) 
	{  // Using softwareSerial to communicate with mp3.
		Serial.println(F("Unable to begin. Possible Reasons:\n "));
		Serial.println(F("1. Connection lost."));
		Serial.println(F("2. SD card may not be inserted yet."));
	}
	Serial.println(F("DFPlayer Mini online."));
}