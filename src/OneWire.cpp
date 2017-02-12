// Include the libraries we need
#include "OneWire.h"


// Bus Configuration
#define ONE_WIRE_BUS0 2 // Bus0 On Pin D1
#define ONE_WIRE_BUS1 0 // Bus1 on Pin D2
#define MaxSensorCount 10  // max num of sensors to be defined per Bus

const int oneWirePinsCount = 2;
#define TEMPERATURE_PRECISION 12

// Bus
OneWire oneWire0(ONE_WIRE_BUS0);
OneWire oneWire1(ONE_WIRE_BUS1);
OneWire owbus[] = {oneWire0, oneWire1};

DallasTemperature sensor[oneWirePinsCount];
int sensorsonBus[oneWirePinsCount];

// Struct Array for DS18B20 Adress / Temp
	typedef struct
	 {
		byte Address[8];
		char temperatureString[6];
	 }  tempSensor;
	 tempSensor sensorValues[MaxSensorCount];

	 void printAddress(byte deviceAddress[8]) {
	 	  for (int i = 0; i < 8; i++)
	 	  {
	 	    if (deviceAddress[i] < 16) Serial.print("0");
	 	    Serial.print(deviceAddress[i], HEX);
	 	  }
	 };

	 void loopOneWire() {
	 // call sensors.requestTemperatures() to issue a global temperature
	 // request to all devices on the bus
	 Serial.print("Requesting temperatures...");
	 for (int i=0; i<oneWirePinsCount; i++) {
	   sensor[i].requestTemperatures();
	 }
	 Serial.println("DONE");
	 delay(1000);
	 for (int i=0; i<oneWirePinsCount; i++) {
	 for (int y=0; y<sensorsonBus[i]; y++) {
	   float temperature=sensor[i].getTempCByIndex(y);
	   Serial.print("Temperature for the sensor ");
	   Serial.print(y);
	   Serial.print(" is ");
	   Serial.println(temperature);
	 }
	 }
	 Serial.println();
	 };


// setup OneWire bus
void setupOneWire(void) {
	// Start up the library on all defined bus-wires
	// actions for every bus
	  for (int i=0; i<oneWirePinsCount; i++)
		  {
        // init bus
            sensor[i].setOneWire(&owbus[i]);
	  	  	  sensor[i].begin();

	  	  // locate devices on the bus
         Homie.getLogger() << "Get num of devices on Bus: " << i << endl;
         sensorsonBus[i] = sensor[i].getDeviceCount();
	  	   Homie.getLogger() << " Found " << sensorsonBus[i] << " devices" << endl;

	        // report parasite power requirements
	          Homie.getLogger() << "Parasite power on Bus is: " << endl;
	          if (sensor[i].isParasitePowerMode())
            {
              Homie.getLogger() << "ON" << endl;
            }
	          else
            {
              Homie.getLogger() << "OFF" << endl;
            }

         // set Temperature Precision
	      //	 sensor[i].setResolution(TEMPERATURE_PRECISION);

        // actions for every sensor on bus
	     for (byte s=0; s<sensorsonBus[i]; s++)
	         {
	           // assigns the next address found to Address[i][0...7]
	    	   if (sensor[i].getAddress(sensorValues[s].Address, s))
	           {
               Serial.print("Sensor with Address ");
  	    		   printAddress(sensorValues[s].Address);
  	    		   Serial.println(" found");
	           }
	    	   else
	    	   {
	    		   Homie.getLogger() << "Unable to find address" << endl;
	    	   }
	    	   // set Temperature Precision
	    	   sensor[i].setResolution(sensorValues[s].Address, TEMPERATURE_PRECISION);
	    	   //TO-DO
           // Set Alarms
	    	  // sensor[i].setHighAlarmTemp(sensorValues[s].Address, 30);
	    	   //sensor[i].setLowAlarmTemp(sensorValues[s].Address, 22);
	    	   // print Infos about Sensor
	    	   Serial.print("\n-----------------\nInfos about sensor with Address");
	    	   printAddress(sensorValues[s].Address);
	    	   Serial.print(":\n");
	    	   Serial.print("Resolution: ");
	    	   Serial.print(sensor[i].getResolution(sensorValues[s].Address));
	    	   Serial.print("Bits \nAlarm low / high / has alarm: ");
	    	   Serial.print(sensor[i].getLowAlarmTemp(sensorValues[s].Address), DEC);
	    	   Serial.print(" / ");
	    	   Serial.print(sensor[i].getHighAlarmTemp(sensorValues[s].Address), DEC);
	    	   Serial.print(" / ");
	    	   (sensor[i].hasAlarm(sensorValues[s].Address)) ? Serial.print(" TRUE ") : Serial.print(" FALSE ");
	    	   Serial.print(" \n Temperature: ");
	    	   Serial.print(sensor[i].getTempC(sensorValues[s].Address));
	    	   Serial.print("\n-----------------\n");
           Serial.print("\n-----------------\n");
           Serial.print("\n-----------------\n");
           Serial.print("\n-----------------\n");
	         }; //for sensor
	   }; // for bus

		Homie.getLogger() << "[setupOneWire] finished" << endl;
}; // setup
