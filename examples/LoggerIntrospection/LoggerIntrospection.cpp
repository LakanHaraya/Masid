/**
 * @file LoggerIntrospection.ino
 * @brief Halimbawa ng paggamit ng mga introspection methods ng Masid logger.
 * 
 * Layunin nitong ipakita kung paano ma-access ang kasalukuyang configuration
 * ng logger: log name, tag, severity level, log format, at bilang ng log entries.
 * 
 * Bahagi ng Proyektong LundayHangin  
 * Target board: Arduino Uno o katumbas
 * 
 * @author Lakan Haraya
 * @date 2025-06-28
 */

#include <Masid.h>

// Dummy timestamp
const char* getTimestamp() {
    return "[00:01:23]";
}

// Subukang palitan sa Masid::DEBUG! Tingnan ang mahika!
// Subukan ding palitan ang log format!!!
Masid logger(Serial, "FlightCtrl", Masid::WARNING, getTimestamp, Masid::JSON, "CTRL");

void setup() {
    Serial.begin(115200);
    while (!Serial);

    logger.notice("Ulat ng kasalukuyang configuration:");

    // Log Name
    logger.info(String("Pangalan ng logger: ") + logger.getLogName());

    // Tag
    logger.info(String("Tag: ") + logger.getTag());

    // Severity
    logger.info(String("Minimum Severity (enum): ") + logger.getMinSeverity());
    logger.info(String("Minimum Severity (label): ") + logger.getMinSeverityLabel());

    // Log Format
    logger.info(String("Log Format (enum): ") + logger.getLogFormat());
    logger.info(String("Log Format (label): ") + logger.getLogFormatLabel());

    // Log Count
    logger.info(String("Bilang ng mga log entry: ") + logger.getLogCount());

    // Sample log para mapataas ang log count
    logger.error("Isang halimbawa ng error log.");
    logger.debug("Hindi ito lalabas kung naka-set sa WARNING.");

    // Ulat ng updated log count
    logger.info(String("Updated log count: ") + logger.getLogCount());
}

void loop() {
    // Walang laman — introspection lang ang focus
}
