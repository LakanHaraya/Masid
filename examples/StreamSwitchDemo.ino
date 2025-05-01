#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Masid.h>

const int chipSelect = 10;
const char* logFileName = "MASID003.TXT";

File logFile;
Masid logger(Serial, "SALUYAN", DEBUG, nullptr, "demo");  // Simula sa Serial stream

void setup() {
    Serial.begin(115200);
    while (!Serial);

    Serial.println("Sinisimulan ang SD kard...");
    if (!SD.begin(chipSelect)) {
        Serial.println("Nabigo ang inisyalisasyon ng SD kard!");
        return;
    }

    if (SD.exists(logFileName)) {
        Serial.println("Binubura ang lumang MASID003.TXT...");
        SD.remove(logFileName);
    }

    logFile = SD.open(logFileName, FILE_WRITE);
    if (!logFile) {
        Serial.println("Hindi mabuksan ang MASID003.TXT para sa pagsusulat.");
        return;
    }

    Serial.println("Nakabukas ang MASID003.TXT para sa pagsusulat.");

    // Logging sa Serial (default)
    logger.info("Hakbang 1.0: Logging sa `Serial` stream muna.");
    logger.notice("Hakbang 1.1: Hinahanda ang kalibrasyon ng sensor...");
    
    // Palitan ng SD card file bilang stream
    logger.setStream(logFile);
    logger.info("Hakbang 2.0: Logging sa file ng SD kard na MASID003.TXT.");
    logger.warning("Hakbang 2.1: Mataas na boltahe!");
    logger.error("Hakbang 2.2: Nabigong magsimula ang ultrasonikong sensor.");

    // Balik sa Serial stream
    logger.setStream(Serial);
    logger.debug("Hakbang 3.0: Bumalik sa `Serial` stream.");
    logger.notice("Hakbang 3.1: Tsinetsek ang estado ng mga subsistema...");

    logFile.close();
    Serial.println("Naisara ang log file.\n");

    // Basahin at ipakita ang nilalaman ng log file
    Serial.println("Laman ng MASID003.TXT:");
    File readFile = SD.open(logFileName);
    if (readFile) {
        while (readFile.available()) {
            Serial.write(readFile.read());
        }
        readFile.close();
    } else {
        Serial.println("Hindi mabuksan ang MASID003.TXT para basahin.");
    }

    Serial.print("\nKabuoang bilang ng log entry: ");
    Serial.println(logger.getLogCount());
}

void loop() {
    // Walang kailangan sa loop sa demo na ito
}
