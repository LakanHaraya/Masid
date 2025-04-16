#include <Arduino.h>
#include <MuntingMasid.h>

// Dummy timestamp function (optional)
const char* fakeTimestamp() {
    return "[00:00:01]";
}

// Lumikha ng MuntingMasid instance
MuntingMasid masid(Serial, "Airship", DEBUG, fakeTimestamp);

void setup() {
    Serial.begin(115200);
    delay(1000);

    // Ipakita lang ang severity label at mensahe
    masid.showTimestamp(false);   // Huwag ipakita ang timestamp
    masid.showAppName(false);     // Huwag ipakita ang app name
    masid.showTag(false);         // Huwag ipakita ang tag
    masid.showSeverityLabel(true); // Ipakita ang severity

    masid.info("Nag-umpisa ang sistema.");
    masid.warning("Maaaring mababa ang boltahe.");
    masid.error("Hindi mahanap ang sensor.");
}

void loop() {
    // Walang ginagawa sa loop
}
