#include <Servo.h>

const int leftMicPin = A0;   // Left microphone (e.g., facing left)
const int rightMicPin = A1;  // Right microphone (e.g., facing right)

const int LEFT_WHEEL_PIN = 13;
const int RIGHT_WHEEL_PIN = 12;

// Settings
const int samplesPerMic = 20;      // Number of readings per mic sample
const int soundBalanceThreshold = 30;  // How much louder one side needs to be to rotate
const int veryLoudThreshold = 600;     // Loudness level to stop completely
const int moveForwardTime = 100;       // Move time per adjustment (in ms)
const int rotateAdjustmentTime = 80;   // Rotate time for small adjustment

Servo leftWheel, rightWheel;

void setup() {
  Serial.begin(9600);
  leftWheel.attach(LEFT_WHEEL_PIN);
  rightWheel.attach(RIGHT_WHEEL_PIN);
 
  stopMotors();
  delay(500);

  Serial.println("🔍 Starting continuous sound tracking...");
}

void loop() {
  int leftLevel = measureMic(leftMicPin);
  int rightLevel = measureMic(rightMicPin);

  Serial.print("Left: ");
  Serial.print(leftLevel);
  Serial.print(" | Right: ");
  Serial.println(rightLevel);

  // Check if very loud sound detected
  if (leftLevel >= veryLoudThreshold || rightLevel >= veryLoudThreshold) {
    Serial.println("🎯 VERY LOUD sound detected. Stopping.");
    stopMotors();
    while (true); // Stay stopped forever
  }

  // Determine which way to rotate
  int diff = leftLevel - rightLevel;

  if (abs(diff) < soundBalanceThreshold) {
    // Sounds are balanced → Move forward
    Serial.println("🚗 Driving forward...");
    driveForward(moveForwardTime);
  }
  else if (diff > 0) {
    // Left louder → Turn left slightly
    Serial.println("↩️ Adjusting left...");
    rotateLeft(rotateAdjustmentTime);
  }
  else {
    // Right louder → Turn right slightly
    Serial.println("↪️ Adjusting right...");
    rotateRight(rotateAdjustmentTime);
  }
}

// --- Helper Functions ---

int measureMic(int micPin) {
  long total = 0;
  for (int i = 0; i < samplesPerMic; i++) {
    total += analogRead(micPin);
    delay(2);
  }
  return total / samplesPerMic;
}

void driveForward(int duration) {
  leftWheel.write(0);    // Adjusted for your wheel setup
  rightWheel.write(180); // Adjusted for your wheel setup
  delay(duration);
  stopMotors();
}

void rotateLeft(int duration) {
  leftWheel.write(0);    // Left wheel backward
  rightWheel.write(0);   // Right wheel forward (inverted)
  delay(duration);
  stopMotors();
}

void rotateRight(int duration) {
  leftWheel.write(180);  // Left wheel forward
  rightWheel.write(180); // Right wheel backward (inverted)
  delay(duration);
  stopMotors();
}

void stopMotors() {
  leftWheel.write(90);
  rightWheel.write(90);
}
