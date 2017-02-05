/*
 *   Tested with "WiFi Smart Socket ESP8266 MQTT"
 *   and "Sonoff - WiFi Wireless Smart Switch ESP8266 MQTT"
 *
 *   The Relay could be toggeled with the physical pushbutton
*/
#include <Homie.h>

#include "defaults.h"
#include "ota.h"
#include "OneWire.h"

const int TEMP_INTERVAL = 10;                   // seconds
unsigned long last_temp_sent = 0;

// -----------------------------------------------------------------------------
// Welcome MSG
// -----------------------------------------------------------------------------

void welcome() {

    delay(2000);
    Serial.printf("%s %s\n", (char *) APP_NAME, (char *) APP_VERSION);
    Serial.printf("%s\n%s\n\n", (char *) APP_AUTHOR, (char *) APP_WEBSITE);
    Serial.printf("Device: %s\n", (char *) WiFi.hostname().c_str());
    Serial.printf("ChipID: %06X\n", ESP.getChipId());
    Serial.printf("Last reset reason: %s\n", (char *) ESP.getResetReason().c_str());
    Serial.printf("Memory size: %d bytes\n", ESP.getFlashChipSize());
    Serial.printf("Free heap: %d bytes\n", ESP.getFreeHeap());
    FSInfo fs_info;
    if (SPIFFS.info(fs_info)) {
        Serial.printf("File system total size: %d bytes\n", fs_info.totalBytes);
        Serial.printf("            used size : %d bytes\n", fs_info.usedBytes);
        Serial.printf("            block size: %d bytes\n", fs_info.blockSize);
        Serial.printf("            page size : %d bytes\n", fs_info.pageSize);
        Serial.printf("            max files : %d\n", fs_info.maxOpenFiles);
        Serial.printf("            max length: %d\n", fs_info.maxPathLength);
    }
    Serial.println();
    Serial.println();

}



// -----------------------------------------------------------------------------
// Setup Hardware
// -----------------------------------------------------------------------------

void setupHardware() {

      Serial.begin(SERIAL_BAUDRATE);
      Serial.println();
      Serial.println();
      Homie.getLogger() << "[setupHardware] finished" << endl;

}

// -----------------------------------------------------------------------------
// Setup Homie
// -----------------------------------------------------------------------------

void setupHomie() {
  Homie_setFirmware(APP_NAME, APP_VERSION);
  Homie.disableResetTrigger();
  Homie.setup();
 Homie.getLogger() << "[setupHomie] finished" << endl;
}


// -----------------------------------------------------------------------------
// setup
// -----------------------------------------------------------------------------

void setup() {
  setupHardware();
  setupHomie();
  welcome();
  otaSetup();
  setupOneWire();
}

// -----------------------------------------------------------------------------
// Loop
// -----------------------------------------------------------------------------

void loop() {
  Homie.loop();
  otaLoop();
  loopOneWire();
}
