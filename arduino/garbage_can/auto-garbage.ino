#include <Servo.h>

const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
const int servoPin = 9;

const long triggerDistance = 20;
const int doorDelay = 4000;

Servo servo;

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
   servo.attach(servoPin);
   closeDoor();
}

void loop() {
   pinMode(pingPin, OUTPUT);
   pinMode(echoPin, INPUT);

   long cm = detectDistance();
   if (cm <= triggerDistance) {
     openDoor();
     delay(doorDelay);
     closeDoor();
   }

   delay(100);
}

void openDoor() {
  int i;
  for (i = 180; i >= 30; i -= 10) {
    servo.write(i);
    delay(100);
  }
}

void closeDoor() {
  servo.write(180);
}

long detectDistance() {
   long duration, inches, cm;

   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   duration = pulseIn(echoPin, HIGH);
   inches = microsecondsToInches(duration);
   cm = microsecondsToCentimeters(duration);
   Serial.print(inches);
   Serial.print("in, ");
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();

   return cm;
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
