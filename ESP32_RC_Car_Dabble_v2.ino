/*
  ESP32 RC Car - Dabble app control with adjustable speed
  ----------------------------------------------------------
  Wiring (same pins as your existing build):
    IN1 -> GPIO 27   (left motor direction)
    IN2 -> GPIO 26
    IN3 -> GPIO 25   (right motor direction)
    IN4 -> GPIO 33
    ENA -> GPIO 14   (left motor speed / PWM) - remove the jumper cap, wire this pin
    ENB -> GPIO 32   (right motor speed / PWM) - remove the jumper cap, wire this pin
    ESP32 GND -> L298N GND -> battery negative (common ground)

  Uses the ESP32 core 3.x PWM API (ledcAttach/ledcWrite work directly on
  the pin number - no separate channel number needed, unlike older cores).
*/

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

// Left motor
int enableLeftMotor = 14;   // ENA
int leftMotorPin1   = 27;   // IN1
int leftMotorPin2   = 26;   // IN2

// Right motor
int enableRightMotor = 32;  // ENB
int rightMotorPin1   = 25;  // IN3
int rightMotorPin2   = 33;  // IN4

#define MAX_MOTOR_SPEED 255   // 0-255. If disconnects persist, try lowering this
                              // (e.g. 180) to reduce the motor's startup current spike.

const int PWMFreq = 1000;     // 1 kHz
const int PWMResolution = 8;  // 8-bit -> speed range 0-255

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
  // Right motor direction
  if (rightMotorSpeed < 0) {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
  } else if (rightMotorSpeed > 0) {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  } else {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
  }

  // Left motor direction
  if (leftMotorSpeed < 0) {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
  } else if (leftMotorSpeed > 0) {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  } else {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
  }

  ledcWrite(enableRightMotor, abs(rightMotorSpeed));
  ledcWrite(enableLeftMotor, abs(leftMotorSpeed));
}

void setUpPinModes()
{
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  // Set up PWM for speed - new core 3.x API, attaches straight to the pin
  ledcAttach(enableRightMotor, PWMFreq, PWMResolution);
  ledcAttach(enableLeftMotor, PWMFreq, PWMResolution);

  rotateMotor(0, 0);
}

void setup()
{
  Serial.begin(115200);
  setUpPinModes();
  Dabble.begin("MyBluetoothCar");
  Serial.println("Waiting for Dabble app to connect...");
}

// Current speed each motor is actually running at right now (ramps toward target)
int currentRightSpeed = 0;
int currentLeftSpeed  = 0;

const int RAMP_STEP  = 20;  // how much speed can change per loop pass - lower = gentler start
const int LOOP_DELAY = 15;  // ms between loop passes - controls how fast the ramp moves

// Moves 'current' one step closer to 'target', without overshooting it
int rampTowards(int current, int target, int step)
{
  if (current < target) {
    current += step;
    if (current > target) current = target;
  } else if (current > target) {
    current -= step;
    if (current < target) current = target;
  }
  return current;
}

void loop()
{
  int targetRightSpeed = 0;
  int targetLeftSpeed  = 0;

  Dabble.processInput();

  if (GamePad.isUpPressed()) {
    targetRightSpeed = MAX_MOTOR_SPEED;
    targetLeftSpeed  = MAX_MOTOR_SPEED;
  }

  if (GamePad.isDownPressed()) {
    targetRightSpeed = -MAX_MOTOR_SPEED;
    targetLeftSpeed  = -MAX_MOTOR_SPEED;
  }

  if (GamePad.isLeftPressed()) {
    targetRightSpeed = MAX_MOTOR_SPEED;
    targetLeftSpeed  = -MAX_MOTOR_SPEED;   // pivot turn: right wheel forward, left wheel back
  }

  if (GamePad.isRightPressed()) {
    targetRightSpeed = -MAX_MOTOR_SPEED;
    targetLeftSpeed  = MAX_MOTOR_SPEED;
  }

  // Move gradually toward the target instead of jumping straight to it -
  // this softens the current spike that happens when a motor starts from a dead stop
  currentRightSpeed = rampTowards(currentRightSpeed, targetRightSpeed, RAMP_STEP);
  currentLeftSpeed  = rampTowards(currentLeftSpeed, targetLeftSpeed, RAMP_STEP);

  rotateMotor(currentRightSpeed, currentLeftSpeed);

  delay(LOOP_DELAY);
}
