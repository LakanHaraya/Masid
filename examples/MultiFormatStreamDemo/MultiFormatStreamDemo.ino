/**
 * @file MultiFormatStreamDemo.ino
 * @brief Demo ng Masid logging na may magkaibang format: Serial (SIMPLE), SD Card (JSON)
 *
 * Ipinapakita kung paano mag-log sa dalawang stream gamit ang magkakaibang output format.
 * Serial: SIMPLE
 * SD card: JSON
 *
 * Target: Arduino Uno o katumbas
 * SD Module: CS sa pin 10 (default para sa Uno)
 *
 * Author: Lakan Haraya
 * Date: 2025-06-29
 */
#include <Arduino.h>
#include <Masid.h>
#include <SPI.h>
#include <SD.h>

// Static timestamp
const char* getTimestamp() {
    return "[00:01:23]";
}

// SD config
const int chipSelect = 10;
File logFile;

// Gumawa ng Masid logger — default stream ay Serial (gagamitin lang para sa constructor)
Masid logger(Serial, "FlightCtrl", Masid::INFO, getTimestamp, Masid::SIMPLE, "CTRL");

void setup() {
    Serial.begin(115200);
    while (!Serial);

    logger.notice("Simula ng Multi-Format logging demo...");

    // I-initialize ang SD card
    if (!SD.begin(chipSelect)) {
        logger.error("Nabigong simulan ang SD card.");
        return;
    }

    logFile = SD.open("masid.txt", FILE_WRITE);
    if (!logFile) {
        logger.error("Hindi mabuksan ang masid.txt");
        return;
    }

    // Idagdag ang SD log file bilang JSON format
    logger.addFileStream(logFile, Masid::JSON);

    // Sample logs
    logger.info("SD card initialized. Logging sa Serial at SD.");
    logger.warning("Paalala: Mababang boltahe.");
    logger.error("Nawawalang sensor!");

    logFile.flush();  // Siguraduhin ang pagsusulat
}

void loop() {
    // Wala tayong log sa loop. Static demo lamang.
}
