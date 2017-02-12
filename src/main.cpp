/*
 *   Tested with "WiFi Smart Socket ESP8266 MQTT"
 *   and "Sonoff - WiFi Wireless Smart Switch ESP8266 MQTT"
 *
 *   The Relay could be toggeled with the physical pushbutton
*/
#include "main.hpp"

const int TEMP_INTERVAL = 10;                   // seconds
unsigned long last_temp_sent = 0;

ds18b20MultiNode TempNode1("Bus1", DS18B20_BUS1);
//ds18b20MultiNode TempNode2("Bus2", DS18B20_BUS2);

// -----------------------------------------------------------------------------
// Setup Hardware
// -----------------------------------------------------------------------------

void setupHardware() {

      Serial.begin(SERIAL_BAUDRATE);
      Serial.println();
      Serial.println();
      Homie.getLogger() << "[setupHardware] finished\n\n\n" << endl;

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
  welcome();
  otaSetup();
  setupHomie();
//setupOneWire();
}


// -----------------------------------------------------------------------------
// Loop
// -----------------------------------------------------------------------------

void loop() {
  Homie.loop();
  otaLoop();
// loopOneWire();
}
