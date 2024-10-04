#include <Arduino.h>

// Define pin numbers for motor control
constexpr int DIR_PIN = 2;    // Direction pin
constexpr int STEP_PIN = 5;   // Step pin
constexpr int ENABLE_PIN = 6; // Enable pin

unsigned long startMillis;  // Variable to store the start time
unsigned long currentMillis; // Variable to store the current time
constexpr unsigned long period = 60; // Total time of looping (s) for 1 hour

void setup() {
  pinMode(STEP_PIN, OUTPUT);  // Set STEP_PIN as output
  pinMode(DIR_PIN, OUTPUT);   // Set DIR_PIN as output
  pinMode(ENABLE_PIN, OUTPUT); // Set ENABLE_PIN as output
  startMillis = millis();  // Record the start time
}

// Set stepper driver to 1200 steps/rev
constexpr int STEPScw = 200; // Define number of steps for clockwise rotation

void constantAccelcw() {
  int delays[STEPScw]; // Array to store delay times
  const float angle = 1;     // Angle of rotation
  const float accel = 0.005; // Acceleration value
  const float c0 = 900 * sqrt(2 * angle / accel) * 0.67703; // Calculate initial delay
  float lastDelay = 0; // Variable to store the last delay
  const int highSpeed = 10;  // Minimum delay (maximum speed)
  
  // Calculate delay times for acceleration
  for (int i = 0; i < STEPScw; i++) {
    float d = c0;
    if (i > 0) {
      d = lastDelay - (2 * lastDelay) / (4 * i + 1);
    }
    if (d < highSpeed) {
      d = highSpeed;
    }
    delays[i] = static_cast<int>(d);
    lastDelay = d;
  }
  
  // Execute steps with increasing speed (acceleration)
  for (int i = 0; i < STEPScw; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(delays[i]);
    digitalWrite(STEP_PIN, LOW);
  }
  
  // Execute steps with decreasing speed (deceleration)
  for (int i = 0; i < STEPScw; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(delays[STEPScw - i - 1]);
    digitalWrite(STEP_PIN, LOW);
  }
}

constexpr int STEPSccw = 50; // Define number of steps for counter-clockwise rotation

void constantAccelccw() {
  int delays[STEPSccw]; // Array to store delay times
  const float angle = 1;      // Angle of rotation
  const float accel = 0.0005; // Acceleration value (slower than clockwise)
  const float c0 = 900 * sqrt(2 * angle / accel) * 0.67703; // Calculate initial delay
  float lastDelay = 0;  // Variable to store the last delay
  const int highSpeed = 10;   // Minimum delay (maximum speed)
  
  // Calculate delay times for acceleration
  for (int i = 0; i < STEPSccw; i++) {
    float d = c0;
    if (i > 0) {
      d = lastDelay - (2 * lastDelay) / (4 * i + 1);
    }
    if (d < highSpeed) {
      d = highSpeed;
    }
    delays[i] = static_cast<int>(d);
    lastDelay = d;
  }
  
  // Execute steps with increasing speed (acceleration)
  for (int i = 0; i < STEPSccw; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(delays[i]);
    digitalWrite(STEP_PIN, LOW);
  }
  
  // Execute steps with decreasing speed (deceleration)
  for (int i = 0; i < STEPSccw; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(delays[STEPSccw - i - 1]);
    digitalWrite(STEP_PIN, LOW);
  }
}

void loop() {
  currentMillis = millis(); // Get the current time
  if (currentMillis - startMillis >= period * 1000) { // Check if the total runtime has been reached
    return; // Exit the loop if the time has elapsed
  }
  
  // Perform clockwise and counter-clockwise rotations
  digitalWrite(DIR_PIN, LOW);  // Set direction to clockwise
  constantAccelcw();           // Execute clockwise rotation
  digitalWrite(DIR_PIN, HIGH); // Set direction to counter-clockwise
  constantAccelccw();          // Execute counter-clockwise rotation
  delay(50);                  // Wait for 50 milliseconds before next cycle
}
