#include <Arduino.h>

void setup() {
    Serial.begin(115200);  // USB Serial for viewing output
}

void loop() {
    while (Serial.available()) {
        char c = Serial.read();
        Serial.write(c);  // Echo to monitor
    }
}
