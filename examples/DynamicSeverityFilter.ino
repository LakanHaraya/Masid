#include <Arduino.h>
#include <Masid.h>

Masid logger(Serial, "DynamicSeverity", INFO);

void setup() {
    Serial.begin(115200);
    logger.info("Info message - lalabas.");
    logger.debug("Debug message - hindi lalabas.");

    logger.setMinSeverity(DEBUG);
    logger.debug("Ngayon lalabas na ang debug message.");
}

void loop() {
    // ...
}
