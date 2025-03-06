
#include <Servo.h>

Servo leftServo;
Servo rightServo;

const int leftServoPin = 12;  
const int rightServoPin = 13;

void setup() {
  leftServo.attach(leftServoPin);
  rightServo.attach(rightServoPin);
  Serial.begin(9600);

  Serial.println("Moving Forward...");
  leftServo.write(180);
  rightServo.write(0);
  delay(2000);

  Serial.println("Stopping...");
  leftServo.write(0);
  rightServo.write(0);
  delay(2000);
}

void loop {
  
}

