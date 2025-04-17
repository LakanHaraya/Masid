#include <Arduino.h>
#include <MuntingMasid.h>

// Regular function para sa custom timestamp
const char* customTimestamp() {
  static char timestamp[20];
  sprintf(timestamp, "%lums", millis());  // Ang custom timestamp na gusto mong ipakitatimestamp
  return timestamp;
}

// Gumawa ng instance ng MuntingMasid
Stream& serialStream = Serial;
MuntingMasid logger(serialStream, "LoggerObj", DEBUG, nullptr);

void setup() {
    // Inisyalisa ang Serial Monitor
    Serial.begin(115200);
    while (!Serial);
}

void loop() {
  // Itakda ang DEFAULT timestamp function
  logger.setTsFunc(nullptr);
  logger.notice("Gamit ang DEFAULT timestamp.");

  delay(1000);

  // Itakda ang CUSTOM timestamp function
  logger.setTsFunc(customTimestamp);
  logger.notice("Gamit ang CUSTOM timestamp.");

  delay(1000);
}
