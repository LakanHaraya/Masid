#include <Arduino.h>
#include <MuntingMasid.h>

MuntingMasid logger(Serial, "DynamicSeverity", INFO);

void setup() {
    Serial.begin(115200);
    logger.info("Info message - lalabas.");
    logger.debug("Debug message - hindi lalabas.");

    logger.setMinimumSeverity(DEBUG);
    logger.debug("Ngayon lalabas na ang debug message.");
}

void loop() {
    // ...
}
