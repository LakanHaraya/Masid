#include <Arduino.h>
#include <MuntingMasid.h>

// Halimbawa ng Timestamp Function
const char* myTimestampFunc() {
    static char timestamp[20];
    sprintf(timestamp, "[%lu]", millis());  // Gamitin ang millis() para sa dynamic timestamp
    return timestamp;
}

void setup() {
    // I-setup ang Serial Monitor
    Serial.begin(115200);
    while (!Serial) { ; }

    // Gumawa ng MuntingMasid object
    MuntingMasid logger(Serial, "LundayHanginApp", DEBUG, myTimestampFunc, "INIT");

    // Mag-log gamit ang default timestamp function
    logger.info("Ito ay isang info log gamit ang default timestamp.");

    // Baguhin ang timestamp function gamit ang setTsFunc
    logger.setTsFunc([]() -> const char* { return "[Custom Time]"; }); // Gumagamit ng lambda function

    // Mag-log gamit ang bagong timestamp function
    logger.warning("Pagtanggap ng babala gamit ang custom na timestamp.");
}

void loop() {
    // Walang ginagawa sa loop sa pagkakataong ito
}
