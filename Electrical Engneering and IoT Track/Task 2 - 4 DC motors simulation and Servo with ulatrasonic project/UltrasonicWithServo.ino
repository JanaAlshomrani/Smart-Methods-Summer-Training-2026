#include <Servo.h>

Servo myServo;

const int trigPin = 3;
const int echoPin = 2;
const int servoPin = 8;
const int ledPin = 4;

long duration;
float distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  myServo.attach(servoPin);
  myServo.write(0);

  Serial.begin(9600);
}

float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2.0;
  return distance;
}

void loop() {
  float d = getDistance();

  Serial.print("Distance: ");
  Serial.print(d);
  Serial.println(" cm");

  if (d > 0 && d <= 10) {
    myServo.write(90);
    digitalWrite(ledPin, HIGH);
  } else {
    myServo.write(0);
    digitalWrite(ledPin, LOW);
  }

  delay(200);
}