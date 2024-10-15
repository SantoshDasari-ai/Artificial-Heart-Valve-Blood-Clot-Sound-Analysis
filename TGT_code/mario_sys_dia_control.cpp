#include <Arduino.h> // Include the Arduino library for basic functions

// Define pin numbers for motor control
constexpr int DIR_PIN = 2;    // Direction pin
constexpr int STEP_PIN = 5;   // Step pin
constexpr int ENABLE_PIN = 8; // Enable pin

constexpr int SYSTOLE_STEPS = 622;    // Number of steps for systole phase
constexpr int DIASTOLE_STEPS = round(SYSTOLE_STEPS/3);   // Number of steps for diastole phase
constexpr int HEART_RATE = 75;        // Target heart rate in beats per minute
constexpr int CYCLE_DELAY = (60000 / HEART_RATE) / 2; // Half cycle delay in milliseconds (systole or diastole duration)

// Overall runtime in seconds
constexpr unsigned long RUNTIME_SECONDS = 60; // Set runtime here (e.g., 60 seconds)
unsigned long runtimeMillis = RUNTIME_SECONDS * 1000UL; // Convert runtime to milliseconds
unsigned long startMillis;

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

void rotateMotor(bool clockwise, int steps) {
  int delays[steps];              // Array to store delay times for acceleration/deceleration
  const float angle = 1;          // Angle of rotation per step
  const float accel = 0.003;      // Adjusted acceleration value for smoother movement
  const float c0 = 900 * sqrt(2 * angle / accel) * 0.67703; // Calculate initial delay
  float lastDelay = 0;            // Variable to store the last delay
  const int highSpeed = 20;       // Minimum delay (maximum speed), adjusted for larger motor

  // Calculate delay array for acceleration
  for (int i = 0; i < steps; i++) {
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
  digitalWrite(DIR_PIN, clockwise ? HIGH : LOW);
  delayMicroseconds(5); // Direction signal needs at least 5μs setup time before the pulse

  // Accelerate and rotate motor
  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(delays[i]);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(2.5); // Pulse width should be at least 2.5μs
  }

  // Decelerate (reverse the array)
  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(delays[steps - i - 1]);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(2.5); // Pulse width should be at least 2.5μs
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
  rotateMotor(true, SYSTOLE_STEPS);
  delay(CYCLE_DELAY); // Delay to simulate diastole phase

  // Counterclockwise rotation (simulate diastole)
  rotateMotor(false, DIASTOLE_STEPS);
}