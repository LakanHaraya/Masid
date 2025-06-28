/**
 * @file LogFormatDemo.ino
 * @brief Halimbawa ng paggamit ng iba't ibang log format: PLAIN, CSV, at JSON.
 * 
 * Ipinapakita ng sketch na ito kung paano palitan ang output format ng Masid logger
 * gamit ang `setLogFormat()` at `getLogFormat()`.  
 * Layunin nitong ipakita ang versatility ng logger para sa iba't ibang application:
 * - Human-readable (PLAIN)
 * - Spreadsheet-ready (CSV)
 * - Machine-parsable (JSON)
 * 
 * Bahagi ng Proyektong LundayHangin  
 * Target board: Arduino Uno o katumbas
 * 
 * @author Lakan Haraya
 * @date 2025-06-28
 */

#include <Masid.h>

// Dummy timestamp function
const char* getTimestamp() {
    return "[00:00:42]";
}

// Instantiate the logger
Masid logger(Serial, "LogDemo", Masid::INFO, getTimestamp, "TEST");

void setup() {
    Serial.begin(115200);
    while (!Serial);

    // -------- PLAIN FORMAT --------
    logger.setLogFormat(Masid::PLAIN);
    logger.notice("Ito ay plain log output.");
    logger.info("Gamit ito sa Serial Monitor.");
    
    // -------- CSV FORMAT --------
    logger.setLogFormat(Masid::CSV);
    logger.warning("Ito ay CSV-formatted log.");
    logger.error("Maaaring i-import sa spreadsheet.");

    // -------- JSON FORMAT --------
    logger.setLogFormat(Masid::JSON);
    logger.alert("Ito ay JSON log.");
    logger.debug("Makina ang magbabasa nito (kung DEBUG ay pinagana).");

    // -------- Log Format Reflection --------
    Masid::LogFormat fmt = logger.getLogFormat();
    logger.setLogFormat(Masid::PLAIN);
    logger.info(String("Kasulukuyang format (bilang enum): ") + fmt);
}

void loop() {
    // Wala dito para sa simpleng demonstrasyon
}
