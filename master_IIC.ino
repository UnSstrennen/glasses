#include <SoftwareSerial.h>

#include <Wire.h>
#include <DFRobotDFPlayerMini.h>

const byte RX = 10;
const byte TX = 11;
SoftwareSerial music_player(RX, TX);
DFRobotDFPlayerMini myDFPlayer;

byte a;
byte b;
byte c;

void setup() 
{
  Serial.begin(9600);  // start serial for output
  player_settings();
  Wire.begin();        // join i2c bus (address optional for master)
}

void loop() 
{
	Wire.requestFrom(1, 1);    // request 6 bytes from slave device #8

	while (Wire.available()) 
	{ // slave may send less than requested
		a = Wire.read(); // receive a byte as character
		a = map (a, 0, 170, 30, 0);
		Serial.println(a);         // print the character
	}

  delay(30);

	Wire.requestFrom(2, 1);    // request 6 bytes from slave device #8

	while (Wire.available()) 
	{ // slave may send less than requested
		b = Wire.read(); // receive a byte as character
		b = map (b, 0, 170, 30, 0);
		Serial.println(b);         // print the character
	}

	delay(30);

	Wire.requestFrom(3, 1);    // request 6 bytes from slave device #8

	while (Wire.available()) 
	{ // slave may send less than requested
		c = Wire.read(); // receive a byte as character
		c = map (c, 0, 170, 30, 0);
	Serial.println(c);         // print the character
	}

	delay(30);

	playL(a);
	playC(b);
	playR(c);

	delay(10);
}

int volumeDecrease = 5; //уменьшил громкость

void playL(byte volume) 
{
// играем L с громкостью volume
	myDFPlayer.volume(volume-volumeDecrease);
// номер дорожки без нулей в начале
	const byte TRACK_NUMBER = 1;
	myDFPlayer.play(TRACK_NUMBER);
}

void playC(byte volume) 
{
// играем C с громкостью volume
	myDFPlayer.volume(volume-volumeDecrease);
// номер дорожки без нулей в начале
	const byte TRACK_NUMBER = 3;
	myDFPlayer.play(TRACK_NUMBER);
}

void playR(byte volume) 
{
// играем C с громкостью volume
	myDFPlayer.volume(volume-volumeDecrease);
// номер дорожки без нулей в начале
	const byte TRACK_NUMBER = 5;
	myDFPlayer.play(TRACK_NUMBER);
}

void player_settings() 
{
	music_player.begin (9600); // открываем софт-порт
	Serial.println();
	Serial.println(F("DFRobot DFPlayer Mini Demo"));
	Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

	if (!myDFPlayer.begin(music_player)) 
	{  //Use softwareSerial to communicate with mp3.
		Serial.println(F("Unable to begin:"));
		Serial.println(F("1.Please recheck the connection!"));
		Serial.println(F("2.Please insert the SD card!"));
	}
	Serial.println(F("DFPlayer Mini online."));
}
