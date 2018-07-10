#include <Wire.h>

#define Trigger 6
#define Echo 7

int dist = 0;
int Time = 0;

void setup() 
{
	Wire.begin(3);                // join i2c bus with address #
	Wire.onRequest(requestEvent); // register event
	pinMode(Trigger, OUTPUT);
	pinMode(Echo, INPUT);
}

void loop() 
{
	GetInfo();
//dist = map(dist, 0, 270, 30, 0);
	requestEvent();
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() 
{
  Wire.write(dist);
}

void GetInfo() 
{
	digitalWrite(Trigger, LOW);
	delayMicroseconds(5);
	digitalWrite(Trigger, HIGH);
	delayMicroseconds(10);
	digitalWrite(Trigger, LOW);
	Time = pulseIn(Echo, HIGH);
	dist = Time / 58;
	delay(8);
}
