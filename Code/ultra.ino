// Define pin connections
const int trigPin = 9;
const int echoPin = 10;

void setup() {
    Serial.begin(9600);  // Initialize serial communication
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop() {
    long duration;
    float distance;

    // Send a 10-microsecond pulse to trigger pin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read the echo pin and calculate distance
    duration = pulseIn(echoPin, HIGH);
    distance = (duration * 0.0343) / 2;  // Convert to cm

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    delay(500);  // Wait before next reading
}


