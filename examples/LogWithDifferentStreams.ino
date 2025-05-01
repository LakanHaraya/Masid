#include <Arduino.h>
#include <Masid.h>

// Dalawang magkahiwalay na logger na parehong gumagamit ng Serial
Masid loggerMain(Serial, "MAIN", DEBUG);
Masid loggerSensor(Serial, "SENSOR", DEBUG);

// Simpleng timestamp function (oras sa millis)
const char* getMillisAsTimestamp() {
    static char buffer[16];
    snprintf(buffer, sizeof(buffer), "%lu", millis());
    return buffer;
}

void setup() {
    Serial.begin(115200);
    while (!Serial); // Hintayin ang Serial kung kinakailangan

    // Kung gusto mong lagyan ng timestamp
    loggerMain = Masid(Serial, "MAIN", DEBUG, getMillisAsTimestamp);
    loggerSensor = Masid(Serial, "SENSOR", DEBUG, getMillisAsTimestamp);

    loggerMain.info("Sistema ay nag-umpisa");
    loggerSensor.debug("Handa na ang sensor module");
}

void loop() {
    loggerMain.notice("Lahat ay nasa normal na kalagayan.");
    delay(1000);

    loggerSensor.debug("Kasalukuyang pagbasa: 23.5C");
    delay(1000);
}
