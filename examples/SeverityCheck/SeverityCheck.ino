/**
 * @file SeverityCheck.ino
 * @brief Halimbawa ng paggamit ng `getMinSeverity()` at `getMinSeverityLabel()` para sa pagsiyasat ng log level.
 * 
 * Ipinapakita kung paano gamitin ang dalawang method na ito upang:
 * - Ipakita sa user ang kasalukuyang logging threshold (e.g., INFO, DEBUG)
 * - Magdesisyon kung dapat maglabas ng partikular na mga log
 * 
 * Bahagi ng Proyektong LundayHangin
 * Target board: Arduino Uno o katumbas
 * 
 * @author Lakan Haraya - lakanharaya@gmail.com
 * @date 2025-06-28
 */

#include <Masid.h>

// Dummy timestamp (para lang may laman)
const char* getTimestamp() {
    return "[00:00:00]";
}

// I-setup ang logger: magsimula sa NOTICE level
Masid logger(Serial, "SYS", Masid::NOTICE, getTimestamp, "CORE");

void setup() {
    Serial.begin(115200);
    while (!Serial);  // Hintayin ang Serial Monitor

    // === IPAKITA ANG KASALUKUYANG SEVERITY LEVEL ===
    logger.notice(String("Kasalukuyang severity threshold: ") + logger.getMinSeverityLabel());

    // === LOGIC BATAY SA KASALUKUYANG LEVEL ===
    // Halimbawa: kung masyadong mababa ang threshold (DEBUG), maaaring maglabas ng babala
    Masid::Severity level = logger.getMinSeverity();

    if (level <= Masid::DEBUG) {
        logger.warning("Logging level, masyadong mababa — posibleng epekto sa performance.");
    } else if (level <= Masid::INFO) {
        logger.info("Logging, itinakda sa antas pang-impormasyon.");
    } else {
        logger.notice("Logging, nasa production mode.");
    }

    // === IPAKITA ANG PAGBABAGO NG LEVEL ===
    logger.setMinSeverity(Masid::DEBUG);  // Palitan ang threshold

    logger.notice(String("Severity pinalitan sa: ") + logger.getMinSeverityLabel());

    // Patunay na nakababa na ang threshold
    if (logger.getMinSeverity() <= Masid::DEBUG) {
        logger.debug("Debugging logs ay aktibo na.");
    }
}

void loop() {
    // Wala dito para sa simpleng demo
}
