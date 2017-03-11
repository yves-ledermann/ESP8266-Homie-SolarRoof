/*
 *   Tested with "WiFi Smart Socket ESP8266 MQTT"
 *   and "Sonoff - WiFi Wireless Smart Switch ESP8266 MQTT"
 *
 *   The Relay could be toggeled with the physical pushbutton
*/
#include "main.hpp"

Node_ds18b20Multi TempNode1("Bus1", DS18B20_BUS1);
Node_ds18b20Multi TempNode2("Bus2", DS18B20_BUS2);

Node_AnalogIn LDRNode1("LDR", A0);
//Node_UltrasonicSerial DistanceNode1("Usonic1", USonic_PIN1);

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

//  TempNode1.setDebug(TRUE);
//  TempNode2.setDebug(TRUE);

  TempNode1.setInterval(30);
  TempNode2.setInterval(30);

  LDRNode1.setInterval(2);
//DistanceNode1.setDebug(FALSE);
}


// -----------------------------------------------------------------------------
// Loop
// -----------------------------------------------------------------------------

void loop() {
  Homie.loop();
  otaLoop();
}
