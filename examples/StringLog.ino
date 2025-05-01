#include <Arduino.h>
#include <Masid.h>

// Gumamit tayo ng Serial bilang output stream
Masid masid(Serial, "SensorApp");

void setup() {
  Serial.begin(115200);
    delay(500); // Hintayin ang serial

    masid.info("Pagsisimula ng sistema...");
}

void loop() {
    int sensorValue = analogRead(A0);
    float voltage = sensorValue * (5.0 / 1023.0);
    float tempC = voltage * 100.0;

    masid.debug("Hilaw: " + String(sensorValue));
    masid.info("Boltahe: " + String(voltage, 2) + " V");
    masid.notice("Temperatura: " + String(tempC, 1) + " °C");

    if (tempC > 50.0) {
        masid.warning("Mainit! Lagpas 50°C");
    }

    delay(2000); // Bawat 2 segundo
}
