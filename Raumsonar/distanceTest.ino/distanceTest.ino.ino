/*      Ultrasonic sensor Pins:
        Trig : Trigger (INPUT)- Pin 11
        Echo: Echo (OUTPUT)   - Pin 12
        Servo (OUTPUT)        - PIN  3
 */
#include <Servo.h>
 
#define MAX_DISTANCE 100

int trigPin = 11;    //Trig - green Jumper
int echoPin = 12;    //Echo - yellow Jumper
long duration, dist;
short cm, tmp = 0;
Servo myservo;

void setup() {
  Serial.begin (115200);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myservo.attach(3);

}
 
void loop()
{
    myservo.write(10);
    //delay(500);
    for(int i=0; i<=180; i++){
      myservo.write(i);
      sendTrigger();
      Serial.print(catchDistance());
      Serial.println(" cm   ");  
      delay(10);
      }
      delay(1000);
}

void sendTrigger(){
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}

int catchDistance(){
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(echoPin, HIGH);
  dist = (duration/2) / 29.1;
  if(dist < MAX_DISTANCE)
    tmp=dist;
  return tmp;  
}

