#include <Arduino.h> // Include the Arduino library for basic functions

// Define pin numbers for motor control
constexpr int DIR_PIN = 2;    // Direction pin
constexpr int STEP_PIN = 5;   // Step pin
constexpr int ENABLE_PIN = 8; // Enable pin

unsigned long startMillis;      // Variable to store the start time
unsigned long currentMillis;    // Variable to store the current time
constexpr unsigned long period = 3600; // Run for 1 hour (seconds)
constexpr int STEPS = 200;      // Number of steps for both CW and CCW

void setup() {
  pinMode(STEP_PIN, OUTPUT);     // Set STEP_PIN as output
  pinMode(DIR_PIN, OUTPUT);      // Set DIR_PIN as output
  pinMode(ENABLE_PIN, OUTPUT);   // Set ENABLE_PIN as output
  startMillis = millis();        // Record the start time
  digitalWrite(ENABLE_PIN, LOW); // Enable motor driver
}

void constantAccel(bool clockwise) {
  int delays[STEPS];              // Array to store delay times
  const float angle = 1;          // Angle of rotation
  const float accel = 0.005;      // Acceleration value
  const float c0 = 900 * sqrt(2 * angle / accel) * 0.67703; // Calculate initial delay
  float lastDelay = 0;            // Variable to store the last delay
  const int highSpeed = 10;       // Minimum delay (maximum speed)

  // Calculate delay array for acceleration
  for (int i = 0; i < STEPS; i++) {
    float d = c0;
    if (i > 0) {
      d = lastDelay - (2 * lastDelay) / (4 * i + 1);
    }
    if (d < highSpeed) {
      d = highSpeed;
    }
    delays[i] = static_cast<int>(d); // Cast delay to int
    lastDelay = d;                    // Update last delay
  }

  // Set motor direction
  digitalWrite(DIR_PIN, clockwise ? LOW : HIGH);

  // Move the motor with acceleration
  for (int i = 0; i < STEPS; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(delays[i]);
    digitalWrite(STEP_PIN, LOW);
  }

  // Decelerate (reverse the array)
  for (int i = 0; i < STEPS; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(delays[STEPS - i - 1]);
    digitalWrite(STEP_PIN, LOW);
  }
}

void loop() {
  currentMillis = millis(); // Get the current time
  if (currentMillis - startMillis >= period * 1000UL) {
    digitalWrite(ENABLE_PIN, HIGH); // Disable motor driver after period
    return; // Exit loop if the period has elapsed
  } else {
    // Clockwise rotation
    constantAccel(true);
    
    // Counterclockwise rotation (back to starting position)
    constantAccel(false);
    
    delay(50); // Wait for 50 milliseconds before next cycle
  }
}
