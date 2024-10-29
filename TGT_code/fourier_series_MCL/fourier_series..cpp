#include <Arduino.h> // Include the Arduino library for basic functions

// Define pin numbers for motor control
constexpr int DIR_PIN = 2;    // Direction pin
constexpr int STEP_PIN = 5;   // Step pin
constexpr int ENABLE_PIN = 8; // Enable pin

constexpr int SYSTOLE_STEPS = 622;    // Number of steps for systole phase
constexpr int DIASTOLE_STEPS = round(SYSTOLE_STEPS / 3); // Number of steps for diastole phase
constexpr int HEART_RATE = 75;        // Target heart rate in beats per minute
constexpr int CYCLE_DELAY = (60000 / HEART_RATE) / 2; // Half cycle delay in milliseconds (systole or diastole duration)

// Overall runtime in seconds
constexpr unsigned long RUNTIME_SECONDS = 60; // Set runtime here (e.g., 60 seconds)
unsigned long runtimeMillis = RUNTIME_SECONDS * 1000UL; // Convert runtime to milliseconds
unsigned long startMillis;

// Angular acceleration profile (example values for demonstration)
constexpr int NUM_POINTS = 100; // Number of points in the profile
float angularAccelProfile[NUM_POINTS] = { /* Fill with angular acceleration values over time */ };

void setup() {
  pinMode(STEP_PIN, OUTPUT);     // Set STEP_PIN as output
  pinMode(DIR_PIN, OUTPUT);      // Set DIR_PIN as output
  pinMode(ENABLE_PIN, OUTPUT);   // Set ENABLE_PIN as output

  digitalWrite(ENABLE_PIN, LOW); // Enable motor driver
  startMillis = millis();         // Record the start time
}

void enableMotor(bool enable) {
  if (enable) {
    digitalWrite(ENABLE_PIN, LOW); // Enable motor driver (ENA is active low)
  } else {
    digitalWrite(ENABLE_PIN, HIGH); // Disable motor driver
  }
}

void rotateMotor(bool clockwise, int steps, float *accelProfile) {
  float angularVelocity = 0;     // Initial angular velocity
  float lastAngularVelocity = 0; // Variable to store the last angular velocity
  float timeStep = CYCLE_DELAY / NUM_POINTS; // Time step between profile points (ms)

  // Set motor direction
  digitalWrite(DIR_PIN, clockwise ? HIGH : LOW);
  delayMicroseconds(5); // Direction signal needs at least 5μs setup time before the pulse

  // Rotate motor with varying speed based on angular acceleration profile
  for (int i = 0; i < steps; i++) {
    int profileIndex = (i * NUM_POINTS) / steps; // Calculate profile index based on step
    float angularAccel = accelProfile[profileIndex]; // Get current angular acceleration

    // Update angular velocity using numerical integration (Euler's method)
    angularVelocity = lastAngularVelocity + angularAccel * (timeStep / 1000.0); // Convert ms to seconds

    // Prevent negative or too small angular velocities
    if (angularVelocity < 0.1) {
      angularVelocity = 0.1;
    }

    // Calculate delay based on angular velocity
    int stepDelay = static_cast<int>((1.0 / angularVelocity) * 1000000.0); // Delay in microseconds

    // Perform step
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(2.5); // Pulse width should be at least 2.5μs

    // Update last angular velocity
    lastAngularVelocity = angularVelocity;
  }
}

void loop() {
  // Check if runtime has elapsed
  unsigned long currentMillis = millis();
  if (currentMillis - startMillis >= runtimeMillis) {
    enableMotor(false); // Disable motor driver
    return; // Exit the loop if the runtime is over
  }

  enableMotor(true); // Enable motor driver

  // Clockwise rotation (simulate systole)
  rotateMotor(true, SYSTOLE_STEPS, angularAccelProfile);

  // Counterclockwise rotation (simulate diastole)
  rotateMotor(false, DIASTOLE_STEPS, angularAccelProfile);
}
