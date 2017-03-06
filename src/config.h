#ifndef SRC_CONFIG_H
#define SRC_CONFIG_H

//------------------------------------------------------------------------------
// SET BY PLATFORMIO
//------------------------------------------------------------------------------

//#define DEBUG_PORT              Serial

// -----------------------------------------------------------------------------
// HARDWARE
// -----------------------------------------------------------------------------

#define SERIAL_BAUDRATE         115200

#define APP_NAME                "homie-SolarRoof"
#define APP_VERSION             "2.0.1"
#define APP_AUTHOR              "yves@laedis.ch"
#define APP_WEBSITE             "http://yves.laedis.ch"


#define DS18B20_BUS1            2 // Bus0 On Pin D3?
#define DS18B20_BUS2            0 // Bus1 on Pin D4?
#define USonic_PIN1             4 // Bus1 on Pin D2?


// -----------------------------------------------------------------------------
// Configuration
// -----------------------------------------------------------------------------

#define OTA_PASS                "assugrin"
#define OTA_PORT                8266

// -----------------------------------------------------------------------------



#endif /* end of include guard: SRC_CONFIG_H */
