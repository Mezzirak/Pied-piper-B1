#include <Servo.h>
#include <Wire.h>
#include <Adafruit_APDS9960.h>

Servo servoLeft;
Servo servoRight;
Adafruit_APDS9960 apds;

uint16_t r, g, b, c;
const float RED_RATIO_THRESHOLD = 0.3;
const int ROTATION_TIME = 6000;
const int SAMPLE_INTERVAL = 200;
const int MAX_SAMPLES = ROTATION_TIME / SAMPLE_INTERVAL;

float redRatios[MAX_SAMPLES];
unsigned long sampleTimes[MAX_SAMPLES];

void setup() {
  servoLeft.attach(12);
  servoRight.attach(13);
  Serial.begin(9600);
  Serial.println("Starting...");

  if (!apds.begin()) {
    Serial.println("APDS9960 failed to initialize!");
    while (1);
  }
  apds.enableColor(true);

  // Test rotation
  Serial.println("Testing rotation...");
  rotateInPlaceSlowly();
  delay(6000);
  stopMoving();
  delay(1000);
}

void loop() {
  Serial.println("Scanning 360°...");
  unsigned long startTime = millis();
  int sampleIndex = 0;

  rotateInPlaceSlowly();
  while (millis() - startTime < ROTATION_TIME && sampleIndex < MAX_SAMPLES) {
    if (apds.colorDataReady()) {
      apds.getColorData(&r, &g, &b, &c);
      float total = r + g + b;
      float redRatio = (total > 0) ? (float)r / total : 0;

      redRatios[sampleIndex] = redRatio;
      sampleTimes[sampleIndex] = millis() - startTime;

      Serial.print("Sample "); Serial.print(sampleIndex);
      Serial.print(" - R: "); Serial.print(r);
      Serial.print(" G: "); Serial.print(g);
      Serial.print(" B: "); Serial.print(b);
      Serial.print(" Ratio: "); Serial.println(redRatio);

      sampleIndex++;
      delay(SAMPLE_INTERVAL);
    }
  }
  stopMoving();
  delay(500);

  float maxRedRatio = 0;
  int maxIndex = -1;
  for (int i = 0; i < sampleIndex; i++) {
    if (redRatios[i] > maxRedRatio && redRatios[i] > RED_RATIO_THRESHOLD) {
      maxRedRatio = redRatios[i];
      maxIndex = i;
    }
  }

  if (maxIndex >= 0) {
    Serial.print("Max Red Ratio: "); Serial.print(maxRedRatio);
    Serial.print(" at Sample: "); Serial.print(maxIndex);
    Serial.print(" Time: "); Serial.println(sampleTimes[maxIndex]);

    rotateBackSlowly();  // Rotate opposite direction
    delay(sampleTimes[maxIndex]);
    stopMoving();
    delay(1000);

    while (!apds.colorDataReady()) {
      delay(50);
    }
    apds.getColorData(&r, &g, &b, &c);
    float total = r + g + b;
    float verifyRatio = (total > 0) ? (float)r / total : 0;
    Serial.print("Verification - R: "); Serial.print(r);
    Serial.print(" Ratio: "); Serial.println(verifyRatio);

    if (verifyRatio > RED_RATIO_THRESHOLD) {
      Serial.println("Aligned! Moving toward red source...");
      moveForward();
      delay(2000);
      stopMoving();
    } else {
      Serial.println("Alignment failed. Retrying...");
    }
  } else {
    Serial.println("No significant red detected.");
  }

  delay(2000);
}

void rotateInPlaceSlowly() {
  servoLeft.writeMicroseconds(1600);  // Counterclockwise
  servoRight.writeMicroseconds(1600);
}

void rotateBackSlowly() {
  servoLeft.writeMicroseconds(1400);  // Clockwise (adjust as needed)
  servoRight.writeMicroseconds(1400);
}

void moveForward() {
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1700);
}

void stopMoving() {
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}