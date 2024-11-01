#include <AFMotor.h>

// Create motor instances
AF_DCMotor motor1(1); // Motor 1 connected to port 1
AF_DCMotor motor2(2); // Motor 2 connected to port 2
AF_DCMotor motor3(3); // Motor 3 connected to port 3

void setup() {
    // Start with all motors off
    motor1.setSpeed(0);
    motor2.setSpeed(0);
    motor3.setSpeed(0);
}

void loop() {
    moveForward();
    delay(2000); // Move forward for 2 seconds
    stopMotors();
    delay(1000); // Stop for 1 second

    moveBackward();
    delay(2000); // Move backward for 2 seconds
    stopMotors();
    delay(1000); // Stop for 1 second

    turnLeft();
    delay(1000); // Turn left for 1 second
    stopMotors();
    delay(1000); // Stop for 1 second

    turnRight();
    delay(1000); // Turn right for 1 second
    stopMotors();
    delay(1000); // Stop for 1 second
}

// Function to move forward
void moveForward() {
    motor1.setSpeed(255); // Set speed to maximum (0-255)
    motor1.run(FORWARD);
    motor2.setSpeed(255);
    motor2.run(FORWARD);
    motor3.setSpeed(255);
    motor3.run(FORWARD);
}

// Function to move backward
void moveBackward() {
    motor1.setSpeed(255);
    motor1.run(BACKWARD);
    motor2.setSpeed(255);
    motor2.run(BACKWARD);
    motor3.setSpeed(255);
    motor3.run(BACKWARD);
}

// Function to turn left
void turnLeft() {
    motor1.setSpeed(0); // Stop Motor 1
    motor2.setSpeed(255);
    motor2.run(FORWARD);
    motor3.setSpeed(255);
    motor3.run(FORWARD);
}

// Function to turn right
void turnRight() {
    motor1.setSpeed(255);
    motor1.run(FORWARD);
    motor2.setSpeed(0); // Stop Motor 2
    motor3.setSpeed(255);
    motor3.run(FORWARD);
}

// Function to stop all motors
void stopMotors() {
    motor1.setSpeed(0);
    motor1.run(RELEASE); // Release motor control
    motor2.setSpeed(0);
    motor2.run(RELEASE);
    motor3.setSpeed(0);
    motor3.run(RELEASE);
}
