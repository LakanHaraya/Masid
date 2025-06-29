/**
 * @file MultiStreamDemo.ino
 * @brief Demo ng Masid multi-stream logging gamit ang Serial at SD card.
 *
 * Ipinapakita kung paano magsulat ng log sa parehong Serial at SD card file.
 *
 * Target: Arduino Uno (o katumbas) + SD card module
 * Wiring: CS → pin 10 (karaniwan sa Uno)
 *
 * Author: Lakan Haraya
 * Date: 2025-06-28
 */

#include <Masid.h>
#include <SPI.h>
#include <SD.h>

// Kunwariang oras
const char* getTimestamp() {
    return "[00:00:00]";
}

// SD config
const int chipSelect = 10;
File logFile;

// Masid logger — default sa Serial muna
Masid logger(Serial, "FlightCtrl", Masid::INFO, getTimestamp, Masid::CSV, "DEMO");

void setup() {
    Serial.begin(115200);
    while (!Serial);

    logger.notice("Simula ng demo: Serial + SD logging");

    // Initialize SD card
    if (!SD.begin(chipSelect)) {
        logger.error("SD card inis nabigo.");
        return;
    }

    logFile = SD.open("log.csv", FILE_WRITE);
    if (!logFile) {
        logger.error("Hindi mabuksan ang log.csv.");
        return;
    }

    // Idagdag ang SD stream gamit ang safe cast
    logger.addFileStream(logFile);

    // Log entries sa parehong stream
    logger.notice("SD card handa na. Logging sa Serial at SD.");
    logger.info("INFO log: Ligtas ang mga subsystem.");
    logger.warning("WARNING log: Paalala sa boltahe.");
    logger.error("ERROR log: Nawawalang sensor.");
    logFile.flush();  // Siguraduhing naisulat
}

void loop() {
    // Wala tayong ginagawa sa loop; static log lang ito
}
