#include <Arduino.h>
#include <Masid.h>

Masid logger(Serial, "MasidDemo");
int potVal = 0;
float potVoltage = 0.0;

void setup() {
    Serial.begin(115200);
    delay(1000);  // Hintayin muna ang serial monitor

    int temperature = 38;
    String sensor = "DHT22";
    float voltage = 3.76;

    // Mga log
    logger.emergency("NABIGONG SISTEMA!");
    logger.alert("Nadetek ang mataas na temperatura!");
    logger.notice("Kalibrasyon ay nagpapatuloy...");
    logger.info("Pagbasa ng sensor " + sensor + ": " + String(temperature) + "°C");
    logger.debug("Boltahe ng baterya: " + String(voltage) + "V");
}

void loop() {
    // Basahin ang potentiometer value mula sa analog pin A0
    potVal = analogRead(A0);
    
    // I-map ang potentiometer value mula 0-1023 papunta sa 0-5 range
    potVoltage = map(potVal, 0, 1023, 0, 5000) / 1000.0;  // Pag-convert ng value sa Volts (0-5V)

    // Log the potentiometer value at voltage
    logger.info("Potentiometer Value: " + String(potVal) + " | Voltage: " + String(potVoltage, 2) + "V");

    delay(250);  // Maghintay ng 1 segundo bago basahin muli
}
