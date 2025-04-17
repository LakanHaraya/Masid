#include <Arduino.h>
#include <MuntingMasid.h>

char tsBuff[32];
const char* getTimestamp() {
  snprintf(tsBuff, sizeof(tsBuff), "%lums", millis());
  return tsBuff;
}

MuntingMasid masid(Serial, "MasidDemo", DEBUG, nullptr, "KtrlLipad");

void setup() {
  Serial.begin(115200);
  while (!Serial); // Hintayin ang Serial sa ilang boards

  // I-set ang optional na tag
  masid.setTag(nullptr);    // Palitan ng `getTimestamp`

  // (Optional) I-set ang minimum log level (default ay DEBUG)
  masid.setMinSeverity(INFO);   // Palitan ng `DEBUG` o iba pang severity level

  // Mag-log gamit ang iba't ibang severity
  masid.emergency("Nabigo ang sistema!");
  masid.alert("Kritikal na mababa ang baterya!");
  masid.critical("Error sa kalibrasyon ng sensor.");
  masid.error("Hindi tumutugon ang motor.");
  masid.warning("Nadetek ang pagliwas sa altitud.");
  masid.notice("Pumapasok sa modang mababang-lakas.");
  masid.info("Tinaglay ang trangka ng GPS.");
  masid.debug("Simulan ang pag-ulit, temp=27.4°C");
}

void loop() {
  // Walang ginagawa sa loop, one-time lang log sa setup
}
