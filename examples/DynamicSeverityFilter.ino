#include <Arduino.h>
#include <Masid.h>

Masid logger(Serial, "DynamicSeverity", Masid::INFO);

void setup() {
    Serial.begin(115200);
    logger.info("Info message - lalabas.");
    logger.debug("Debug message - hindi lalabas.");

    logger.setMinSeverity(Masid::DEBUG);
    logger.debug("Ngayon lalabas na ang debug message.");
}

void loop() {
    // ...
}
