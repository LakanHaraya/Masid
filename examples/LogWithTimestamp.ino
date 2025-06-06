#include <Arduino.h>
#include <Masid.h>

// Sample timestamp function
const char* currentTimestamp() {
    return "2025-04-12T18:00:00Z";
}

Masid logger(Serial, "TalaOras", Masid::DEBUG, currentTimestamp);

void setup() {
    Serial.begin(115200);
    logger.notice("Nagsimula na ang tala-oras na log.");
}

void loop() {
    // Periodic na log
    delay(3000);
    logger.debug("Oras ay lumilipas...");
}
