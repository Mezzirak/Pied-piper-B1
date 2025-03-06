#include <Servo.h>
#include "Adafruit_APDS9960.h"

// Servo objects and pins
Servo leftServo;
Servo rightServo;
const int leftServoPin = 12;  
const int rightServoPin = 13;

// Color sensor object
Adafruit_APDS9960 apds;

void setup() {
  // Attach servos to their pins
  leftServo.attach(leftServoPin);
  rightServo.attach(rightServoPin);

  // Start serial communication (using 115200 to match the sensor code)
  Serial.begin(115200);

  // Initialize the color sensor
  if (!apds.begin()) {
    Serial.println("Failed to initialize device! Please check your wiring.");
    while (1); // Halt if sensor fails
  } else {
    Serial.println("Device initialized!");
  }

  // Enable color sensing mode
  apds.enableColor(true);

  // Brief initial test: move forward for 2 seconds then stop
  Serial.println("Moving Forward...");
  leftServo.write(180);  // Left servo full speed forward
  rightServo.write(0);   // Right servo full speed forward
  delay(2000);

  Serial.println("Stopping...");
  leftServo.write(90);   // Stop left servo (90 is typically neutral for continuous rotation servos)
  rightServo.write(90);  // Stop right servo
  delay(2000);
}

void loop() {
  // Variables to store color data
  uint16_t r, g, b, c;

  // Wait for color data to be ready
  while (!apds.colorDataReady()) {
    delay(5);
  }

  // Get the color data
  apds.getColorData(&r, &g, &b, &c);

  // Print the color values for debugging
  Serial.print("Red: ");
  Serial.print(r);
  Serial.print(", Green: ");
  Serial.print(g);
  Serial.print(", Blue: ");
  Serial.print(b);
  Serial.print(", Clear: ");
  Serial.println(c);

  // Define a threshold for red detection (adjust as needed)
  const uint16_t redThreshold = 1000;

  // Move forward if red is dominant (above threshold)
  if (r > redThreshold && r > g && r > b) {  // Ensures red is the strongest color
    Serial.println("Red detected! Moving Forward...");
    leftServo.write(180);  // Full speed forward
    rightServo.write(0);   // Full speed forward
  } else {
    Serial.println("No significant red. Stopping...");
    leftServo.write(90);   // Stop
    rightServo.write(90);  // Stop
  }

  delay(500);  // Delay to avoid overwhelming the serial output and servo commands
}
