#include <Arduino.h>
#include <Masid.h>

// Simple timestamp function
const char* getFakeTime() {
    static char buffer[16];
    sprintf(buffer, "%05lu", millis());  // Hal: "01234"
    return buffer;
}

Masid logger(Serial, "MasidTest", DEBUG, getFakeTime, "TEST");

void setup() {
    Serial.begin(115200);
    while (!Serial); // Hintayin ang Serial (lalo na sa Leonardo at ESP32)

    Serial.println("\n[Masid Unit Test]");

    logger.debug("Ito ay debug message.");
    logger.info("Impormasyon lamang.");
    logger.warning("May babala.");
    logger.error("May pagkakamali!");
    logger.critical("Kritikal na isyu.");
    logger.alert("Agarang aksiyon!");
    logger.emergency("Hindi na makapagpatuloy ang sistema!");

    logger.info("Kabuoang log entry: " + String(logger.getLogCount()));

    logger.info("Min Severity: " + String(logger.getMinSeverity()));  // Expected: 7 (DEBUG)
}

void loop() {
    // Walang laman – para lang sa one-shot test sa setup()
}
