#include <Arduino.h>
#include <ESP32Servo.h>

// define servo pins
Servo servos[4][3];
const int servoPins[4][3] = {
    {5, 18, 19},
    {21, 22, 23},
    {34, 35, 32},
    {33, 25, 26},
};

void setup() {
    Serial.begin(115200);

    // initialize servos
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            servos[i][j].attach(servoPins[i][j]);
            servos[i][j].write(90); // set initial position to 90 degrees
        }
    }
}

void loop() {
    Serial.println("Hello World!");
    delay(1000);
}
