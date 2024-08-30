#define DIR_PIN 2
#define STEP_PIN 5
#define ENABLE_PIN 6

unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 10; // total time of looping (s) for 1 hours
void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);
  startMillis = millis();  // start time
}

//set stepper driver to 1200 steps/rev
#define STEPScw 200
void constantAccelcw() {
  int delays[STEPScw];
  float angle = 1;
  float accel = 0.005;
  float c0 = 900 * sqrt( 2 * angle / accel ) * 0.67703;
  float lastDelay = 0;
  int highSpeed = 10;
  for (int i = 0; i < STEPScw; i++) {
    float d = c0;
    if ( i > 0 )
    d = lastDelay - (2 * lastDelay) / (4 * i + 1);
    if ( d < highSpeed )
    d = highSpeed;
    delays[i] = d;
    lastDelay = d;
  }
  // use delays from the array, forward
  for (int i = 0; i < STEPScw; i++) {
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds( delays[i] );
  digitalWrite(STEP_PIN, LOW);
  }
  // use delays from the array, backward
  for (int i = 0; i < STEPScw; i++) {
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds( delays[STEPScw-i-1] );
  digitalWrite(STEP_PIN, LOW);
  }
}

#define STEPSccw 50
void constantAccelccw() {
  int delays[STEPSccw];
  float angle = 1;
  float accel = 0.0005;
  float c0 = 900 * sqrt( 2 * angle / accel ) * 0.67703;
  float lastDelay = 0;
  int highSpeed = 10;
  for (int i = 0; i < STEPSccw; i++) {
  float d = c0;
  if ( i > 0 )
  d = lastDelay - (2 * lastDelay) / (4 * i + 1);
  if ( d < highSpeed )
  d = highSpeed;
  delays[i] = d;
  lastDelay = d;
  }
  // use delays from the array, forward
  for (int i = 0; i < STEPSccw; i++) {
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds( delays[i] );
  digitalWrite(STEP_PIN, LOW);
  }
  // use delays from the array, backward
  for (int i = 0; i < STEPSccw; i++) {
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds( delays[STEPSccw-i-1] );
  digitalWrite(STEP_PIN, LOW);
  }
}

void loop() {
  currentMillis = millis();
  if (currentMillis - startMillis >= period*1000){
    return;
  }
  else{
    digitalWrite(DIR_PIN, LOW);
    constantAccelcw();
    digitalWrite(DIR_PIN, HIGH);
    constantAccelccw();
    delay (50);
  }
}
