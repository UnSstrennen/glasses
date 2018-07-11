#include <Wire.h>

#define Trigger 6
#define Echo 7

int dist = 0;
int Time = 0;
int total = 0;

int outDist = 0;

const int avgTimes = 10;

void setup() 
{
	Wire.begin(2);                // join i2c bus with address #
	Wire.onRequest(requestEvent); // register event
	pinMode(Trigger, OUTPUT);
	pinMode(Echo, INPUT);
  Serial.begin(9600); // Serial port
}

void loop() 
{
	//GetInfo();

  for (int i = 0; i < avgTimes; i++)
  {
    dist = getDistance(Trigger, Echo);
    total += dist;
   }
   outDist = total / avgTimes;
  //Serial.println(total/avgTimes);
  total=0;
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() 
{
  Wire.write(outDist);
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

long getDistance(byte trigPin, byte echoPin) {
  long distacne_cm = getEchoTiming(trigPin, echoPin) * 1.7 * 0.01;
  return distacne_cm;
}

// Определение времени задержки
long getEchoTiming(byte trigPin, byte echoPin) {
  digitalWrite(trigPin, HIGH); // генерируем 10 мкс импульс запуска
  delayMicroseconds(10);  
  digitalWrite(trigPin, LOW);
  // определение на пине echoPin длительности уровня HIGH, мкс:
  long duration = pulseIn(echoPin, HIGH); 
  return duration;
}
