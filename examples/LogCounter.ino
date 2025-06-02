#include <Arduino.h>
#include <Masid.h>

Masid logger(
    Serial,
    "LoopApp",
    Masid::DEBUG,
    []() -> const char* {
        static char buf[16];
        sprintf(buf, "[%lu]", millis());
        return buf;
    },
    "LOOP"
);

unsigned long lastLogTime = 0;

void setup() {
    Serial.begin(115200);
    delay(1000);
    logger.notice("Simula ng loop logger");
}

void loop() {
    if (millis() - lastLogTime > 2000) {
        lastLogTime = millis();

        logger.debug("Tumatakbo pa rin ang sistema...");

        // Bilangin at ipakita ang total log count
        size_t bilang = logger.getLogCount();
        logger.info("Kabuoang logs: " + String(bilang));

        if (bilang > 10) {
            logger.warning("Sobrang dami na ng logs!");
        }
    }
}
