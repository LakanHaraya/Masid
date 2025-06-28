/**
 * @file ConditionalDebugLogging.ino
 * @brief Halimbawa ng paggamit ng `shouldLog()` sa kondisyonal na debug logging.
 * 
 * Ipinapakita ng sketch na ito kung paano maiiwasan ang hindi kinakailangang
 * pag-log (hal., mabigat na sensor reading) gamit ang `shouldLog()`.
 * Sa ganitong paraan, ang mga debug computation ay isinasagawa lamang
 * kung aktibo ang DEBUG level logging.
 * 
 * Pangunahing layunin: I-optimize ang performance sa mga resource-constrained 
 * system tulad ng Arduino sa pamamagitan ng masinop na pag-log.
 * 
 * Bahagi ng Proyektong LundayHangin
 * Target board: Arduino Uno (o katumbas)
 * 
 * @author Lakan Haraya - lakanharaya@gmail.com
 * @date 2025-06-28
 */

#include <Arduino.h>
#include <Masid.h>

// Timestamp function na nagpapabalik ng dummy value (pwede mong palitan ng millis-based kung gusto mo)
const char* dummyTimestamp() {
    return "[12:34:56]";
}

// Sample sensor reader (kunwari mabigat ito)
String readAltitude() {
    delay(10);  // kunwari mabigat ang operasyon
    return String(random(950, 1050));  // kunwari nagbabalik ng altitude sa metro
}

// Setup ng logger
Masid logger(Serial, "LundayHangin", Masid::INFO, dummyTimestamp, "NAB");

void setup() {
    Serial.begin(115200);
    while (!Serial);

    logger.notice("Sinimulan ang tagalista.");

    // I-set sa DEBUG kung nais makita ang mas detalyadong log
    logger.setMinSeverity(Masid::DEBUG);    // Subukang palitan ito sa  Masid::INFO` para sa mas kaunting log
}

void loop() {
    // Halimbawa: conditional debug logging
    if (logger.shouldLog(Masid::DEBUG)) {
        logger.debug("Altitud: " + readAltitude() + " m");
    }

    // Palaging ilalabas kung nasa INFO pataas
    logger.info("Aktibong umuulit...");

    delay(2000);
}