#include <Arduino.h>
#include <MuntingMasid.h>

MuntingMasid logger(Serial, "AplikasyonKo");

void setup() {
    Serial.begin(115200);
    logger.info("Pagsisimula ng programa...");
    logger.error("Isang halimbawa ng pagkakamali.");
}

void loop() {
    // Wala muna dito.
}
