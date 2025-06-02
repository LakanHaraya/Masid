#include <Arduino.h>
#include <Masid.h>

// Timestamp function na nagpapabalik ng dummy value (pwede mong palitan ng millis-based kung gusto mo)
const char* dummyTimestamp() {
    return "[12:34:56]";
}

// I-configure ang Serial at logger
Masid masid(Serial, "KontrolerPad", Masid::INFO, dummyTimestamp);

void setup() {
    Serial.begin(115200);
    delay(1000); // Sandaling paghintay para sa serial monitor

    // Itakda ang opsyonal na tag
    masid.setTag("NAV");

    // Maglog ng iba't ibang mensahe
    masid.info("Handa na ang navigation system.");
    masid.warning("Mababang signal mula sa kompas.");
    masid.error("Nawawala ang GPS lock.");

    // I-clear ang tag at mag-log ulit
    masid.setTag(nullptr);  // Puwede ding `setTag("");`
    masid.notice("Pangkalahatang pagpapatuloy ng operasyon.");
}

void loop() {
    // Wala sa loop para sa halimbawang ito
}
