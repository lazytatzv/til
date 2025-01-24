const float Target = 2.5;
const float Kp = 5; 
const float Ki = 1;
const float Kd = 1;

float x = 0;
float dt;
float pretime;
float P, I, D, preP;
uint8_t duty = 0;
int up = 255; // Max PWM value for Arduino
int down = 0; // Min PWM value

void setup() {
    Serial.begin(9600); // start serial
    pinMode(10, OUTPUT);
}

void loop() {
    // Write the calculated duty to the output pin
    analogWrite(10, duty);

    // Averaging 1000 sensor readings
    x = 0; // Reset x before summing readings
    for(int i = 0; i < 1000; i++) {
        x += analogRead(A0);
    }
    x = 5 * x / 1000 / 1023; // Convert to voltage (0-5V scale)

    // Calculate time delta
    dt = (micros() - pretime) / 1000000.0; // Convert microseconds to seconds
    pretime = micros();

    // Calculate PID terms
    P = Target - x;
    I += P * dt;
    D = (P - preP) / dt;
    preP = P;

    // Update duty cycle based on PID formula
    duty += Kp * P + Kd * D + Ki * I;

    // Clamp duty cycle to valid range (0-255)
    if (duty > up) duty = up;
    if (duty < down) duty = down;

    // Print output for monitoring
    Serial.print("Measured Value: ");
    Serial.print(x);
    Serial.print(" V, Duty: ");
    Serial.println(duty);

    delay(100); // Optional: small delay for stability
}
