#include <Servo.h>

Servo myServo;
int degree;

void setup() {
    Serial.begin(9600); 
    myServo.attach(9); // Attach the servo on pin 9
    degree = 0; // Start at 0 degrees
    myServo.write(degree); // Move servo to starting position
}

void loop() {
    if (!(myServo.attached())) { // Corrected syntax
        Serial.println("Servo is not attached!");
    } else {
        degree += 10; // Increase angle by 10 degrees each loop
        if (degree > 180) { // Limit angle to 180 degrees
            degree = 0; // Reset to 0 if it goes beyond 180
        }
        myServo.write(degree); // Set servo to new angle
        Serial.print("Servo angle: ");
        Serial.println(degree); // Print the current angle
    }
    delay(1000); // Wait 1 second
}
