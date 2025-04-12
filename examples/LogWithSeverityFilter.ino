#include <Arduino.h>
#include <MuntingMasid.h>

MuntingMasid logger(Serial, "FilterDemo");

void setup() {
    Serial.begin(115200);
    logger.setMinimumSeverity(ERROR);

    logger.debug("Hindi ito lalabas.");
    logger.warning("Hindi rin ito lalabas.");
    logger.error("Ito lang ang lalabas.");
    logger.critical("Ito rin lalabas.");
}

void loop() {
    // Wala muna
}