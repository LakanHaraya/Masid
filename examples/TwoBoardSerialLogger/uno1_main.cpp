#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Masid.h>

// Regular function para sa custom timestamp
const char* getTimestamp() {
    static char timestamp[20];
    sprintf(timestamp, "%lums", millis());  // Ang custom timestamp na gusto mong ipakita timestamp
    return timestamp;
  }

SoftwareSerial altSerial(10, 11); // RX, TX

Masid mainLog(Serial, "Pangunahin", DEBUG, getTimestamp, "Puno-1");
Masid altLog(altSerial, "Sekundarya", DEBUG, getTimestamp, "Puno-1");

void setup() {
    Serial.begin(115200);
    altSerial.begin(115200);

    delay(1000);
    mainLog.notice("Sinisimulan ang pangunahin.");
    altLog.notice("Sinisimulan ang sekundarya.");
}

void loop() {
    mainLog.info("Ipinadala sa Serial Monitor.");
    altLog.info("Ipinadala sa SoftwareSerial.");
    delay(3000);
}