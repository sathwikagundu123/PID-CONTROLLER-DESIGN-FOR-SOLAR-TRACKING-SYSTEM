#include <Servo.h>

// Define pins
const int ldrPin1 = A0;
const int ldrPin2 = A1;
const int servoPin = 9;

// PID constants (adjust these for optimal performance)
const float Kp = 0.5;
const float Ki = 0.01;
const float Kd = 0.05;

// Maximum servo rotation angle (adjust as needed)
const int maxAngle = 45;

// Variables for PID control
float error, previousError, integral, derivative;
int servoPosition = 90; // Initial servo position

Servo servo;

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  servo.write(servoPosition);
}

void loop() {
  // Read LDR values
  int sensorValue1 = analogRead(ldrPin1);
  int sensorValue2 = analogRead(ldrPin2);

  // Calculate error based on the difference between LDR readings
  error = sensorValue1 - sensorValue2;

  // Limit the error to the maximum angle
  error = constrain(error, -maxAngle, maxAngle);

  // Calculate integral and derivative terms
  integral += error;
  derivative = error - previousError;
  previousError = error;

  // Calculate PID output
  float output = Kp * error + Ki * integral + Kd * derivative;

  // Constrain output to servo range and maximum angle
  int newPosition = servoPosition + output;
  newPosition = constrain(newPosition, 90 - maxAngle, 90 + maxAngle);

  // Set servo position
  servo.write(newPosition);
  servoPosition = newPosition;

  Serial.println(servoPosition);
  delay(100);
}