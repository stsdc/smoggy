/*
  ESP8266 core for Arduino - 3.0.2 // NodeMCU 1.0; Flash Size: 4MB (FS:1MB OTA:~1019KB)
  Arduino core for the ESP32 - 1.0.6!! // 2.0.0 NOT SUPPORTED!

  Adafruit Unified Sensor - 1.1.4
  DallasTemperature - 3.8.0
*/

// ****** CHOOSE(uncomment) ONLY ONE!!! ******

#define INTL_OLD  // old translataion system
// #define INTL_PL  // polish translataion // EXPERIMENTAL!
// #define INTL_EN  // english translataion // EXPERIMENTAL!

// *******************************************

// ****** CHOOSE(uncomment) ONLY ONE!!! ******



// *******************************************

#define ASYNC_WEBSERVER_ON
#define DISABLE_SMOGLIST

/*

   ESP8266

  Podłączenie czujnikow dla ESP8266 NodeMCU:
  BME280/BMP280: VIN - 3V; GND - G; SCL - D4; SDA - D3
  SHT1x: VIN - 3V; GND - G; SCL - D5; DATA/SDA - D6 wymaga rezystora 10k podłaczonego do VCC
  SHT21/HTU21D: VIN - 3V; GND - G; SCL - D5; SDA - D6
  DHT22: VIN - 3V; GND - G; D7
  DS18B20: VIN - 3V; GND - G; D5 - 4.7k Ohm resistor!
  PMS5003/7003: VIN - VIN/5V; GND - G; Zielony/TX - D1; Niebieski/RX - D2
  HPMA115S0: VIN - VIN/5V; GND - G; TX - D1; RX - D2
  SDS011/21: VIN - 5V; GND - G; TX - D1; RX - D2
  Sensirion SPS30: VIN - 5V; GND - G; TX - D1; RX - D2

  Connection of sensors on ESP8266 NodeMCU:
  BME280/BMP280: VIN - 3V; GND - G; SCL - D4; SDA - D3
  SHT1x: VIN - 3V; GND - G; SCL - D5; DATA/SDA - D6 required pull-up resistor 10k to VCC
  SHT21/HTU21D: VIN - 3V; GND - G; SCL - D5; SDA - D6
  DHT22: VIN - 3V; GND - G; D7
  DS18B20: VIN - 3V; GND - G; D5 - 4.7k Ohm resistor!
  PMS5003/7003: VIN - VIN/5V; GND - G; Green/TX - D1; Blue/RX - D2
  HPMA115S0: VIN - VIN/5V; GND - G; TX - D1; RX - D2
  SDS011/21: VIN - 5V; GND - G; TX - D1; RX - D2
  Sensirion SPS30: VIN - 5V; GND - G; TX - D1; RX - D2


   ESP32

  Podłączenie czujnikow dla ESP32:
  BME280/BMP280: VIN - 3V; GND - G; SCL - D17; SDA - D16
  SHT1x: VIN - 3V; GND - G; SCL - D5; DATA/SDA - D6 wymaga rezystora 10k podłaczonego do VCC
  SHT21/HTU21D: VIN - 3V; GND - G; SCL - D5; SDA - D6
  DHT22: VIN - 3V; GND - G; D7
  DS18B20: VIN - 3V; GND - G; D5 - 4.7k Ohm resistor!
  PMS5003/7003: VIN - VIN/5V; GND - G; TX - D5; RX - D4
  HPMA115S0: VIN - VIN/5V; GND - G; TX - D1; RX - D2
  SDS011/21: VIN - 5V; GND - G; TX - D5; RX - D4
  Sensirion SPS30: VIN - 5V; GND - G; TX - D5; RX - D4

  Connection of sensors on ESP32:
  BME280/BMP280: VIN - 3V; GND - G; SCL - D17; SDA - D16
  SHT1x: VIN - 3V; GND - G; SCL - D5; DATA/SDA - D6 required pull-up resistor 10k to VCC
  SHT21/HTU21D: VIN - 3V; GND - G; SCL - D5; SDA - D6
  DHT22: VIN - 3V; GND - G; D7
  DS18B20: VIN - 3V; GND - G; D5 - 4.7k Ohm resistor!
  PMS5003/7003: VIN - VIN/5V; GND - G; TX - D5; RX - D4
  HPMA115S0: VIN - VIN/5V; GND - G; TX - D1; RX - D2
  SDS011/21: VIN - 5V; GND - G; TX - D5; RX - D4
  Sensirion SPS30: VIN - 5V; GND - G; TX - D5; RX - D4
*/

/*
  ESP8266 PMS7003/BME280_0x76 - NodeMCU 1.0 - 1M SPIFFS --- FS:1MB OTA: ~1019KB

  Szkic używa 580548 bajtów (55%) pamięci programu. Maksimum to 1044464 bajtów.
  Zmienne globalne używają 45888 bajtów (56%) pamięci dynamicznej, pozostawiając 36032 bajtów dla zmiennych lokalnych. Maksimum to 81920 bajtów.

  ASYNC_WEBSERVER_ON + INTL_OLD

  Szkic używa 694529 bajtów (66%) pamięci programu. Maksimum to 1044464 bajtów.
  Zmienne globalne używają 46688 bajtów (56%) pamięci dynamicznej, pozostawiając 35232 bajtów dla zmiennych lokalnych. Maksimum to 81920 bajtów.

  Szkic używa 695897 bajtów (66%) pamięci programu. Maksimum to 1044464 bajtów.
  Zmienne globalne używają 46800 bajtów (57%) pamięci dynamicznej, pozostawiając 35120 bajtów dla zmiennych lokalnych. Maksimum to 81920 bajtów.

  Szkic używa 691393 bajtów (66%) pamięci programu. Maksimum to 1044464 bajtów.
  Zmienne globalne używają 46876 bajtów (57%) pamięci dynamicznej, pozostawiając 35044 bajtów dla zmiennych lokalnych. Maksimum to 81920 bajtów.

  ASYNC_WEBSERVER_ON + INTL_PL

  Szkic używa 662541 bajtów (63%) pamięci programu. Maksimum to 1044464 bajtów.
  Zmienne globalne używają 40528 bajtów (49%) pamięci dynamicznej, pozostawiając 41392 bajtów dla zmiennych lokalnych. Maksimum to 81920 bajtów.


  ================================================================================================================================================

  ESP32 Dev Module PMS7003/BME280_0x76 - 1.9MB APP with OTA - 190KB SPIFFS

  Szkic używa 1375786 bajtów (69%) pamięci programu. Maksimum to 1966080 bajtów.
  Zmienne globalne używają 58664 bajtów (17%) pamięci dynamicznej, pozostawiając 269016 bajtów dla zmiennych lokalnych. Maksimum to 327680 bajtów.

  Szkic używa 1377866 bajtów (70%) pamięci programu. Maksimum to 1966080 bajtów.
  Zmienne globalne używają 58656 bajtów (17%) pamięci dynamicznej, pozostawiając 269024 bajtów dla zmiennych lokalnych. Maksimum to 327680 bajtów.

  *** init homekit support:

  Szkic używa 1543130 bajtów (78%) pamięci programu. Maksimum to 1966080 bajtów.
  Zmienne globalne używają 60808 bajtów (18%) pamięci dynamicznej, pozostawiając 266872 bajtów dla zmiennych lokalnych. Maksimum to 327680 bajtów.

  ASYNC_WEBSERVER_ON

  Szkic używa 1477490 bajtów (75%) pamięci programu. Maksimum to 1966080 bajtów.
  Zmienne globalne używają 58976 bajtów (17%) pamięci dynamicznej, pozostawiając 268704 bajtów dla zmiennych lokalnych. Maksimum to 327680 bajtów.

  Szkic używa 1477750 bajtów (75%) pamięci programu. Maksimum to 1966080 bajtów.
  Zmienne globalne używają 59024 bajtów (18%) pamięci dynamicznej, pozostawiając 268656 bajtów dla zmiennych lokalnych. Maksimum to 327680 bajtów.

*/

#include <Arduino.h>
#include "FS.h"
#include <ArduinoJson.h> // 6.9.0 or later
#ifdef ASYNC_WEBSERVER_ON
#include <ESPAsyncWiFiManager.h> // https://github.com/alanswx/ESPAsyncWiFiManager // 5.11.2021
#else
#include "src/WiFiManager/WiFiManager.h" // https://github.com/tzapu/WiFiManager/tree/development // 5.11.2021 DEV
#endif

#include "../lib/smogly_spiffs.h"
#include "config.h"
#include "../include/defaultConfig.h"

#include "../lib/autoupdate.h"

#ifndef DISABLE_SMOGLIST
#include "../lib/services/smoglist.h"
#endif
#include "../lib/services/luftdaten.h"
#ifdef ARDUINO_ARCH_ESP32
#include "../lib/services/airmonitor.h"
#endif
#include "../lib/services/thing_speak.h"
#include "../lib/services/aqieco.h"
#include "../lib/services/InfluxDbV2.h" // https://github.com/davidgs/ESP8266_Influx_DB_V2 // CUSTOMIZED! 5.11.2021

//        it would be nice to update the InfluxDB library to
// #include "src/services/InfluxDB/InfluxDbClient.h" // https://github.com/tobiasschuerg/InfluxDB-Client-for-Arduino

#ifdef ARDUINO_ARCH_ESP8266 // ESP8266 core for Arduino - 2.6.3 or later
#ifdef ASYNC_WEBSERVER_ON
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#else
#include <ESP8266WebServer.h>
#endif
#include <ESP8266mDNS.h>
#ifndef ASYNC_WEBSERVER_ON
#include <ESP8266HTTPUpdateServer.h>
#endif
#include <SoftwareSerial.h>
#elif defined ARDUINO_ARCH_ESP32 // Arduino core for the ESP32 - 1.0.4-rc1 or later // at 1.0.3 autoupdate doesn't work !!!
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>
#ifdef ASYNC_WEBSERVER_ON
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#else
#include <WebServer.h>
#endif
#include <Update.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <time.h>
#include <HardwareSerial.h>
#endif

#include <PubSubClient.h>
#include <Wire.h>

#include "../lib/providers/TemperatureHumidityPressure.h"
#include "../lib/providers/Dust.h"

static char device_name[20];

static unsigned int DUST_interval = 60 * 1000; // 1 minute
unsigned int previous_DUST_Millis = 0;

static unsigned int SENDING_FREQUENCY_interval = 60 * 1000; // 1 minute
unsigned int previous_SENDING_FREQUENCY_Millis = 0;

static unsigned int SENDING_FREQUENCY_AIRMONITOR_interval = 60 * 1000; // 1 minute
unsigned int previous_SENDING_FREQUENCY_AIRMONITOR_Millis = 0;

static unsigned int SENDING_DB_FREQUENCY_interval = 60 * 1000; // 1 minute
unsigned int previous_SENDING_DB_FREQUENCY_Millis = 0;


static unsigned int REBOOT_interval = 24 * 60 * 60 * 1000; // 24 hours
unsigned int previous_REBOOT_Millis = 0;

// unsigned long time_now_temp = 0;


static float currentTemperature, currentHumidity, currentPressure = 0;
// float currentTemperature_THP1, currentHumidity_THP1, currentPressure_THP1 = 0;
// float currentTemperature_THP2, currentHumidity_THP2, currentPressure_THP2 = 0;

static bool need_update = false;
char SERVERSOFTWAREVERSION[32] = "";
char CURRENTSOFTWAREVERSION[32] = "";

#ifdef ASYNC_WEBSERVER_ON
AsyncWebServer server(80);
#else
#ifdef ARDUINO_ARCH_ESP8266
ESP8266WebServer WebServer(80);
ESP8266HTTPUpdateServer httpUpdater;
#elif defined ARDUINO_ARCH_ESP32
WebServer WebServer(80);
#endif
#endif

WiFiClient espClient;
PubSubClient mqttclient(espClient);

// https://github.com/Yurik72/ESPHap
// HomeKit -- START
#ifdef ARDUINO_ARCH_ESP32
#include <SPIFFS.h>
#endif

#ifdef ARDUINO_ARCH_ESP8266
#include "coredecls.h"
#endif

#ifdef ARDUINO_ARCH_ESP32
extern "C" {
// #include "homeintegration.h"  // https://github.com/Yurik72/ESPHap
}
#endif

#ifdef ARDUINO_ARCH_ESP8266
// #include "homekitintegrationcpp.h" // https://github.com/Yurik72/ESPHap/issues/14 << !!!!
#endif

// #ifdef ARDUINO_ARCH_ESP32
// #include <hapfilestorage.hpp>

// homekit_service_t* hapservice = {0};
String pair_file_name = "/homekit_pair.dat";

// homekit_service_t* homekit_temperature = NULL;
// homekit_service_t* homekit_humidity = NULL;
// homekit_service_t* homekit_pm10_level = NULL;
// homekit_service_t* homekit_pm25_level = NULL;

// homekit_characteristic_t*  pm10_level_characteristic = NULL;
// homekit_characteristic_t*  pm25_level_characteristic = NULL;

// struct device_data_t {
//   float homekit_temperature = 22.0;
//   float homekit_humidity = 50.0;
//   float homekit_pm10_level = 10.0;
//   float homekit_pm25_level = 20.0;
// };
// device_data_t homekit_DeviceData;
// #endif
// HomeKit -- END




#ifndef ASYNC_WEBSERVER_ON
WiFiManager wifiManager;
#endif




#ifdef ARDUINO_ARCH_ESP8266
  File fsDAT = SPIFFS.open(pair_file_name, "r");
#elif defined ARDUINO_ARCH_ESP32
  File fsDAT = SPIFFS.open(pair_file_name, FILE_READ);
#endif





// check TEMP/HUMI/PRESS Sensor - END

void minutesToSeconds() {
  DUST_interval = 1000; // 1 second
  SENDING_FREQUENCY_interval = 1000;
  SENDING_DB_FREQUENCY_interval = 1000;
}

void MQTTreconnect() {
  // Loop until we're reconnected
#ifdef ARDUINO_ARCH_ESP8266
  if (!mqttclient.connected()) {
    Serial.print(F("Attempting MQTT connection..."));
    // Attempt to connect
    //if (mqttclient.connect("ESP8266Client", MQTT_USER, MQTT_PASSWORD)) {
    if (mqttclient.connect(device_name, MQTT_USER, MQTT_PASSWORD)) {
      Serial.println(F("connected"));
    } else {
      Serial.print(F("failed, rc="));
      Serial.print(mqttclient.state());
      Serial.println(F("\n"));
    }
  }
#elif defined ARDUINO_ARCH_ESP32
  if (!mqttclient.connected()) {
    Serial.print(("Attempting MQTT connection..."));
    // Attempt to connect
    //if (mqttclient.connect("ESP8266Client", MQTT_USER, MQTT_PASSWORD)) {
    if (mqttclient.connect(device_name, MQTT_USER, MQTT_PASSWORD)) {
      Serial.println(("connected"));
    } else {
      Serial.print(("failed, rc="));
      Serial.print(mqttclient.state());
      Serial.println(("\n"));
    }
  }
#endif
}

void set_I2C_PINS(String THP_PIN, int i) {
#ifdef ARDUINO_ARCH_ESP8266
  if (i == 1) {
    if (THP_PIN == "D1") {
      FIRST_THP_SDA = 5;
    } else if (THP_PIN == "D2") {
      FIRST_THP_SDA = 4;
    } else if (THP_PIN == "D3") {
      FIRST_THP_SDA = 0;
    } else if (THP_PIN == "D4") {
      FIRST_THP_SDA = 2;
    } else if (THP_PIN == "D5") {
      FIRST_THP_SDA = 14;
    } else if (THP_PIN == "D6") {
      FIRST_THP_SDA = 12;
    } else if (THP_PIN == "D7") {
      FIRST_THP_SDA = 13;
    } else if (THP_PIN == "D8") {
      FIRST_THP_SDA = 15;
    } else if (THP_PIN == "D16") {
      FIRST_THP_SDA = 16;
    } else if (THP_PIN == "D17") {
      FIRST_THP_SDA = 17;
    }
  } else if (i == 2) {
    if (THP_PIN == "D1") {
      FIRST_THP_SCL = 5;
    } else if (THP_PIN == "D2") {
      FIRST_THP_SCL = 4;
    } else if (THP_PIN == "D3") {
      FIRST_THP_SCL = 0;
    } else if (THP_PIN == "D4") {
      FIRST_THP_SCL = 2;
    } else if (THP_PIN == "D5") {
      FIRST_THP_SCL = 14;
    } else if (THP_PIN == "D6") {
      FIRST_THP_SCL = 12;
    } else if (THP_PIN == "D7") {
      FIRST_THP_SCL = 13;
    } else if (THP_PIN == "D8") {
      FIRST_THP_SCL = 15;
    } else if (THP_PIN == "D16") {
      FIRST_THP_SCL = 16;
    } else if (THP_PIN == "D17") {
      FIRST_THP_SCL = 17;
    }
  } else if (i == 3) {
    if (THP_PIN == "D1") {
      SECOND_THP_SDA = 5;
    } else if (THP_PIN == "D2") {
      SECOND_THP_SDA = 4;
    } else if (THP_PIN == "D3") {
      SECOND_THP_SDA = 0;
    } else if (THP_PIN == "D4") {
      SECOND_THP_SDA = 2;
    } else if (THP_PIN == "D5") {
      SECOND_THP_SDA = 14;
    } else if (THP_PIN == "D6") {
      SECOND_THP_SDA = 12;
    } else if (THP_PIN == "D7") {
      SECOND_THP_SDA = 13;
    } else if (THP_PIN == "D8") {
      SECOND_THP_SDA = 15;
    } else if (THP_PIN == "D16") {
      SECOND_THP_SDA = 16;
    } else if (THP_PIN == "D17") {
      SECOND_THP_SDA = 17;
    }
  } else if (i == 4) {
    if (THP_PIN == "D1") {
      SECOND_THP_SCL = 5;
    } else if (THP_PIN == "D2") {
      SECOND_THP_SCL = 4;
    } else if (THP_PIN == "D3") {
      SECOND_THP_SCL = 0;
    } else if (THP_PIN == "D4") {
      SECOND_THP_SCL = 2;
    } else if (THP_PIN == "D5") {
      SECOND_THP_SCL = 14;
    } else if (THP_PIN == "D6") {
      SECOND_THP_SCL = 12;
    } else if (THP_PIN == "D7") {
      SECOND_THP_SCL = 13;
    } else if (THP_PIN == "D8") {
      SECOND_THP_SCL = 15;
    } else if (THP_PIN == "D16") {
      SECOND_THP_SCL = 16;
    } else if (THP_PIN == "D17") {
      SECOND_THP_SCL = 17;
    }
  }
#elif defined ARDUINO_ARCH_ESP32
  if (i == 1) {
    if (THP_PIN == "D1") {
      FIRST_THP_SDA = 8;
    } else if (THP_PIN == "D2") {
      FIRST_THP_SDA = 9;
    } else if (THP_PIN == "D4") {
      FIRST_THP_SDA = 4;
    } else if (THP_PIN == "D5") {
      FIRST_THP_SDA = 5;
    } else if (THP_PIN == "D15") {
      FIRST_THP_SDA = 15;
    } else if (THP_PIN == "D16") {
      FIRST_THP_SDA = 16;
    } else if (THP_PIN == "D17") {
      FIRST_THP_SDA = 17;
    } else if (THP_PIN == "D18") {
      FIRST_THP_SDA = 18;
    } else if (THP_PIN == "D19") {
      FIRST_THP_SDA = 19;
    } else if (THP_PIN == "D21") {
      FIRST_THP_SDA = 21;
    } else if (THP_PIN == "D22") {
      FIRST_THP_SDA = 22;
    } else if (THP_PIN == "D23") {
      FIRST_THP_SDA = 23;
    }
  } else if (i == 2) {
    if (THP_PIN == "D1") {
      FIRST_THP_SCL = 8;
    } else if (THP_PIN == "D2") {
      FIRST_THP_SCL = 9;
    } else if (THP_PIN == "D4") {
      FIRST_THP_SCL = 4;
    } else if (THP_PIN == "D5") {
      FIRST_THP_SCL = 5;
    } else if (THP_PIN == "D15") {
      FIRST_THP_SCL = 15;
    } else if (THP_PIN == "D16") {
      FIRST_THP_SCL = 16;
    } else if (THP_PIN == "D17") {
      FIRST_THP_SCL = 17;
    } else if (THP_PIN == "D18") {
      FIRST_THP_SCL = 18;
    } else if (THP_PIN == "D19") {
      FIRST_THP_SCL = 19;
    } else if (THP_PIN == "D21") {
      FIRST_THP_SCL = 21;
    } else if (THP_PIN == "D22") {
      FIRST_THP_SCL = 22;
    } else if (THP_PIN == "D23") {
      FIRST_THP_SCL = 23;
    }
  } else if (i == 3) {
    if (THP_PIN == "D1") {
      SECOND_THP_SDA = 8;
    } else if (THP_PIN == "D2") {
      SECOND_THP_SDA = 9;
    } else if (THP_PIN == "D4") {
      SECOND_THP_SDA = 4;
    } else if (THP_PIN == "D5") {
      SECOND_THP_SDA = 5;
    } else if (THP_PIN == "D15") {
      SECOND_THP_SDA = 15;
    } else if (THP_PIN == "D16") {
      SECOND_THP_SDA = 16;
    } else if (THP_PIN == "D17") {
      SECOND_THP_SDA = 17;
    } else if (THP_PIN == "D18") {
      SECOND_THP_SDA = 18;
    } else if (THP_PIN == "D19") {
      SECOND_THP_SDA = 19;
    } else if (THP_PIN == "D21") {
      SECOND_THP_SDA = 21;
    } else if (THP_PIN == "D22") {
      SECOND_THP_SDA = 22;
    } else if (THP_PIN == "D23") {
      SECOND_THP_SDA = 23;
    }
  } else if (i == 4) {
    if (THP_PIN == "D1") {
      SECOND_THP_SCL = 8;
    } else if (THP_PIN == "D2") {
      SECOND_THP_SCL = 9;
    } else if (THP_PIN == "D4") {
      SECOND_THP_SCL = 4;
    } else if (THP_PIN == "D5") {
      SECOND_THP_SCL = 5;
    } else if (THP_PIN == "D15") {
      SECOND_THP_SCL = 15;
    } else if (THP_PIN == "D16") {
      SECOND_THP_SCL = 16;
    } else if (THP_PIN == "D17") {
      SECOND_THP_SCL = 17;
    } else if (THP_PIN == "D18") {
      SECOND_THP_SCL = 18;
    } else if (THP_PIN == "D19") {
      SECOND_THP_SCL = 19;
    } else if (THP_PIN == "D21") {
      SECOND_THP_SCL = 21;
    } else if (THP_PIN == "D22") {
      SECOND_THP_SCL = 22;
    } else if (THP_PIN == "D23") {
      SECOND_THP_SCL = 23;
    }
  }
#endif
}

void set_SERIAL_PINS(String DUST_PIN, int i) {
#ifdef ARDUINO_ARCH_ESP8266
  if (i == 1) {
    if (DUST_PIN == "D1") {
      DUST_TX = 5;
    } else if (DUST_PIN == "D2") {
      DUST_TX = 4;
    } else if (DUST_PIN == "D3") {
      DUST_TX = 0;
    } else if (DUST_PIN == "D4") {
      DUST_TX = 2;
    } else if (DUST_PIN == "D5") {
      DUST_TX = 14;
    } else if (DUST_PIN == "D6") {
      DUST_TX = 12;
    } else if (DUST_PIN == "D7") {
      DUST_TX = 13;
    } else if (DUST_PIN == "D8") {
      DUST_TX = 15;
    } else if (DUST_PIN == "D16") {
      DUST_TX = 16;
    } else if (DUST_PIN == "D17") {
      DUST_TX = 17;
    }
  } else if (i == 2) {
    if (DUST_PIN == "D1") {
      DUST_RX = 5;
    } else if (DUST_PIN == "D2") {
      DUST_RX = 4;
    } else if (DUST_PIN == "D3") {
      DUST_RX = 0;
    } else if (DUST_PIN == "D4") {
      DUST_RX = 2;
    } else if (DUST_PIN == "D5") {
      DUST_RX = 14;
    } else if (DUST_PIN == "D6") {
      DUST_RX = 12;
    } else if (DUST_PIN == "D7") {
      DUST_RX = 13;
    } else if (DUST_PIN == "D8") {
      DUST_RX = 15;
    } else if (DUST_PIN == "D16") {
      DUST_RX = 16;
    } else if (DUST_PIN == "D17") {
      DUST_RX = 17;
    }
  }
#elif defined ARDUINO_ARCH_ESP32
  if (i == 1) {
    if (DUST_PIN == "D1") {
      DUST_TX = 8;
    } else if (DUST_PIN == "D2") {
      DUST_TX = 9;
    } else if (DUST_PIN == "D4") {
      DUST_TX = 4;
    } else if (DUST_PIN == "D5") {
      DUST_TX = 5;
    } else if (DUST_PIN == "D15") {
      DUST_TX = 15;
    } else if (DUST_PIN == "D16") {
      DUST_TX = 16;
    } else if (DUST_PIN == "D17") {
      DUST_TX = 17;
    } else if (DUST_PIN == "D18") {
      DUST_TX = 18;
    } else if (DUST_PIN == "D19") {
      DUST_TX = 19;
    } else if (DUST_PIN == "D21") {
      DUST_TX = 21;
    } else if (DUST_PIN == "D22") {
      DUST_TX = 22;
    } else if (DUST_PIN == "D23") {
      DUST_TX = 23;
    }
  } else if (i == 2) {
    if (DUST_PIN == "D1") {
      DUST_RX = 8;
    } else if (DUST_PIN == "D2") {
      DUST_RX = 9;
    } else if (DUST_PIN == "D4") {
      DUST_RX = 4;
    } else if (DUST_PIN == "D5") {
      DUST_RX = 5;
    } else if (DUST_PIN == "D15") {
      DUST_RX = 15;
    } else if (DUST_PIN == "D16") {
      DUST_RX = 16;
    } else if (DUST_PIN == "D17") {
      DUST_RX = 17;
    } else if (DUST_PIN == "D18") {
      DUST_RX = 18;
    } else if (DUST_PIN == "D19") {
      DUST_RX = 19;
    } else if (DUST_PIN == "D21") {
      DUST_RX = 21;
    } else if (DUST_PIN == "D22") {
      DUST_RX = 22;
    } else if (DUST_PIN == "D23") {
      DUST_RX = 23;
    }
  }
#endif
}

// default translation - english


#include "../lib/html/html-content.h"

// library doesnt support arguments :/
#ifdef ASYNC_WEBSERVER_ON

#else
#include "../lib/smogly_webserver.h"
#endif


void setup() {
  Serial.begin(115200);
  yield();

  fs_setup();
  yield();

  // deleteConfig();
  // yield();

  //temporary solution!
  if (SECOND_THP) {
    strcpy(SECOND_THP_MODEL, THP_MODEL);
  }


#ifdef ARDUINO_ARCH_ESP32
  disableCore0WDT();
  // disableCore1WDT(); // ESP32-solo-1 so only CORE0!
#endif

#ifdef INTL_OLD
  loadtranslation(SELECTED_LANGUAGE);
#endif
  yield();

  set_I2C_PINS(CONFIG_FIRST_THP_SDA, 1);
  set_I2C_PINS(CONFIG_FIRST_THP_SCL, 2);

  set_I2C_PINS(CONFIG_SECOND_THP_SDA, 3);
  set_I2C_PINS(CONFIG_SECOND_THP_SCL, 4);

  set_SERIAL_PINS(CONFIG_DUST_TX, 1);
  set_SERIAL_PINS(CONFIG_DUST_RX, 2);

  // DUST SENSOR setup - START
#ifdef DUSTSENSOR_PMS5003_7003_BME280_0x76 or DUSTSENSOR_PMS5003_7003_BME280_0x77
  if (!strcmp(DUST_MODEL, "PMS7003")) {
#ifdef ARDUINO_ARCH_ESP8266
#ifdef ARDUINO_ESP8266_RELEASE_2_6_0
    PMS_Serial.begin(9600, DUST_TX, DUST_RX); // Change TX - D1 and RX - D2 pins -- only for esp8266 core 2.6.0
#else
    PMS_Serial.begin(9600); //PMSx003 serial -- esp8266 core 2.6.1 or later
#endif
#elif defined ARDUINO_ARCH_ESP32
    PMS_Serial.begin(9600, SERIAL_8N1, DUST_TX, DUST_RX); //PMSx003 serial
#endif
    if (FREQUENTMEASUREMENT == true) {
      pms.wakeUp();
#ifdef ASYNC_WEBSERVER_ON
      yield();
      delay(500);
#else
      delay(500);
#endif
      pms.activeMode();
    } else {
      pms.passiveMode();
#ifdef ASYNC_WEBSERVER_ON
      yield();
      delay(500);
#else
      delay(500);
#endif
      pms.sleep();
    }
  }
#elif defined DUSTSENSOR_SDS011_21
  if (!strcmp(DUST_MODEL, "SDS011/21")) {
#ifdef ARDUINO_ARCH_ESP8266
    sds.begin();  //SDS011/21 sensor begin
#elif defined ARDUINO_ARCH_ESP32
    sds_port.begin(9600, SERIAL_8N1, DUST_TX, DUST_RX);  //SDS011/21 sensor begin
    my_sds.begin(&sds_port);
#endif
    if (FREQUENTMEASUREMENT == true) {
#ifdef ARDUINO_ARCH_ESP8266
      sds.wakeup();
      sds.setQueryReportingMode().toString(); // ensures sensor is in 'query' reporting mode
      sds.setContinuousWorkingPeriod().toString(); // ensures sensor has continuous working period - default but not recommended
#elif defined ARDUINO_ARCH_ESP32
      err = my_sds.read(&SDSpm25, &SDSpm10);
      if (!err) {
        Serial.println(("Data from SDS011!\n"));
      }
#endif
    } else {
#ifdef ARDUINO_ARCH_ESP8266
      sds.setCustomWorkingPeriod(1);
      WorkingStateResult state = sds.sleep();
#elif defined ARDUINO_ARCH_ESP32
      err = my_sds.read(&SDSpm25, &SDSpm10);
      if (!err) {
        Serial.println(("Data from SDS011!\n"));
      }
#endif
    }
  }

#ifdef ASYNC_WEBSERVER_ON
  yield();
#else
  delay(10);
#endif

#elif defined DUSTSENSOR_HPMA115S0
  if (!strcmp(DUST_MODEL, "HPMA115S0")) {
#ifdef ARDUINO_ARCH_ESP8266
    hpmaSerial.begin(9600); //HPMA115S0 serial
#elif defined ARDUINO_ARCH_ESP32
    hpmaSerial.begin(9600, SERIAL_8N1, DUST_TX, DUST_RX); //HPMA115S0 serial
#endif
#ifdef ASYNC_WEBSERVER_ON
    yield();
#else
    delay(100);
#endif
    if (FREQUENTMEASUREMENT == true) {
      hpma115S0.Init();
#ifdef ASYNC_WEBSERVER_ON
      yield();
#else
      delay(100);
#endif
      hpma115S0.EnableAutoSend();
#ifdef ASYNC_WEBSERVER_ON
      yield();
#else
      delay(100);
#endif
      hpma115S0.StartParticleMeasurement();
    } else {
      hpma115S0.Init();
#ifdef ASYNC_WEBSERVER_ON
      yield();
#else
      delay(100);
#endif
      hpma115S0.StopParticleMeasurement();
    }
  }
#ifdef ASYNC_WEBSERVER_ON
  yield();
#else
  delay(10);
#endif
#elif defined DUSTSENSOR_SPS30
  if (!strcmp(DUST_MODEL, "SPS30")) {
#ifdef ARDUINO_ARCH_ESP8266
    Serial.println(F("Trying to connect to SPS30..."));
#elif defined ARDUINO_ARCH_ESP32
    Serial.println(("Trying to connect to SPS30..."));
#endif
    // set driver debug level
    sps30.EnableDebugging(SPS30_DEBUG);

    // set pins to use for softserial and Serial1 on ESP32
    if (DUST_TX != 0 && DUST_RX != 0) sps30.SetSerialPin(DUST_RX, DUST_TX);

    // Begin communication channel;
    if (sps30.begin(SP30_COMMS) == false) {
      Errorloop("could not initialize communication channel.", 0);
    }

    // check for SPS30 connection
    if (sps30.probe() == false) {
      Errorloop("could not probe / connect with SPS30.", 0);
    } else {
#ifdef ARDUINO_ARCH_ESP8266
      Serial.println(F("Detected SPS30."));
#elif defined ARDUINO_ARCH_ESP32
      Serial.println(("Detected SPS30."));
#endif
    }
    // reset SPS30 connection
    if (sps30.reset() == false) {
      Errorloop("could not reset.", 0);
    }

    // read device info
    GetDeviceInfo();

    // do Auto Clean interval
    // SetAutoClean();

    // start measurement
    if (sps30.start() == true) {
#ifdef ARDUINO_ARCH_ESP8266
      Serial.println(F("Measurement started"));
#elif defined ARDUINO_ARCH_ESP32
      Serial.println(("Measurement started"));
#endif
    } else {
      Errorloop("Could NOT start measurement", 0);
    }
    // clean now requested
    if (SPS30_PERFORMCLEANNOW) {
      // clean now
      if (sps30.clean() == true) {
#ifdef ARDUINO_ARCH_ESP8266
        if (sps30.clean() == true) {
          Serial.println(F("fan-cleaning manually started\n"));
        } else {
          Serial.println(F("Could NOT manually start fan-cleaning\n"));
        }
#elif defined ARDUINO_ARCH_ESP32
        if (sps30.clean() == true) {
          Serial.println(("fan-cleaning manually started\n"));
        } else {
          Serial.println(("Could NOT manually start fan-cleaning\n"));
        }
#endif
      }
    }

    if (SP30_COMMS == I2C_COMMS) {
      if (sps30.I2C_expect() == 4) {
#ifdef ARDUINO_ARCH_ESP8266
        Serial.println(F(" !!! Due to I2C buffersize only the SPS30 MASS concentration is available !!! \n"));
#elif defined ARDUINO_ARCH_ESP32
        Serial.println((" !!! Due to I2C buffersize only the SPS30 MASS concentration is available !!! \n"));
#endif
      }
    }
  }
#else // If no dust sensor has been defined - use DUSTSENSOR_PMS5003_7003_BME280_0x76
  if (!strcmp(DUST_MODEL, "PMS7003")) {
#ifdef ARDUINO_ARCH_ESP8266
#ifdef ARDUINO_ESP8266_RELEASE_2_6_0
    PMS_Serial.begin(9600, DUST_TX, DUST_RX); // Change TX - D1 and RX - D2 pins -- only for esp8266 core 2.6.0
#else
    PMS_Serial.begin(9600); //PMSx003 serial -- esp8266 core 2.6.1 or later
#endif
#elif defined ARDUINO_ARCH_ESP32
    PMS_Serial.begin(9600, SERIAL_8N1, DUST_TX, DUST_RX); //PMSx003 serial
#endif
    if (FREQUENTMEASUREMENT == true) {
      pms.wakeUp();
#ifdef ASYNC_WEBSERVER_ON
      yield();
      delay(500);
#else
      delay(500);
#endif
      pms.activeMode();
    } else {
      pms.passiveMode();
#ifdef ASYNC_WEBSERVER_ON
      yield();
#else
      delay(500);
#endif
      pms.sleep();
    }
  }
#endif

  yield();
  // DUST SENSOR setup - END

  if (SENDING_FREQUENCY < DUST_TIME) {
    SENDING_FREQUENCY = DUST_TIME;
  }
  if (SENDING_DB_FREQUENCY == 0) {
    SENDING_DB_FREQUENCY = SENDING_FREQUENCY;
  }

  yield();

  if (FREQUENTMEASUREMENT == true) {
    minutesToSeconds();
  }

  if (strcmp(DUST_MODEL, "Non")) {
    DUST_interval = DUST_interval * DUST_TIME;
  }
  if (DEEPSLEEP_ON == true) {
    if (LUFTDATEN_ON or AQI_ECO_ON or AIRMONITOR_ON or SMOGLIST_ON or THINGSPEAK_ON or INFLUXDB_ON or MQTT_ON) {
      SENDING_FREQUENCY_interval = SENDING_FREQUENCY_interval * SENDING_FREQUENCY;
    }
#ifdef ARDUINO_ARCH_ESP32
#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  int(SENDING_FREQUENCY_interval/1000)        /* Time ESP32 will go to sleep (in seconds) */
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    Serial.println(("Setup ESP32 to sleep for every ") + String(TIME_TO_SLEEP) + (" Seconds\n"));
#endif
  } else {
    if (LUFTDATEN_ON or AQI_ECO_ON or AIRMONITOR_ON or SMOGLIST_ON) {
      SENDING_FREQUENCY_interval = SENDING_FREQUENCY_interval * SENDING_FREQUENCY;
      if (AIRMONITOR_ON) {
        if (SENDING_FREQUENCY < 3) {
          SENDING_FREQUENCY_AIRMONITOR_interval = SENDING_FREQUENCY_AIRMONITOR_interval * 3; // * 3 -- API restriction - <28 requests per hour
        } else {
          SENDING_FREQUENCY_AIRMONITOR_interval = SENDING_FREQUENCY_AIRMONITOR_interval * SENDING_FREQUENCY;
        }
      }
    }
    if (THINGSPEAK_ON or INFLUXDB_ON or MQTT_ON) {
      SENDING_DB_FREQUENCY_interval = SENDING_DB_FREQUENCY_interval * SENDING_DB_FREQUENCY;
    }
  }
  /*
    Serial.println("SENDING_FREQUENCY: " + String(SENDING_FREQUENCY));
    Serial.println("SENDING_FREQUENCY_AIRMONITOR_interval: " + String(SENDING_FREQUENCY_AIRMONITOR_interval));
    Serial.println("SENDING_FREQUENCY_interval: " + String(SENDING_FREQUENCY_interval));
    Serial.println("DUST_TIME: " + String(DUST_TIME));
    Serial.println("SENDING_DB_FREQUENCY: " + String(SENDING_DB_FREQUENCY));
    Serial.println("");
  */
  yield();

  // TEMP/HUMI/PRESS Sensor seturp - START
  if (!strcmp(THP_MODEL, "BME280")) {
#ifdef ARDUINO_ARCH_ESP8266
    //Wire.begin(0, 2);
    //Wire.begin(FIRST_THP_SDA, FIRST_THP_SCL);
    BMESensor.begin(FIRST_THP_SDA, FIRST_THP_SCL);
    if (SECOND_THP) {
      BMESensor_2.begin(SECOND_THP_SDA, SECOND_THP_SCL);
    }
#elif defined ARDUINO_ARCH_ESP32
    // #define BME280_ADD 0x76
    // bme.begin(BME280_ADD);
    // bme.begin();
    bool bmeStatus = bme.begin();
    if (!bmeStatus) {
      Serial.println("\nCould not find a valid BME280 sensor, check wiring!\n");
    }
#endif
  } else if (!strcmp(THP_MODEL, "BMP280")) {
    //Wire.begin(0, 2);
    Wire.begin(FIRST_THP_SDA, FIRST_THP_SCL);
    bmp.begin();
  } else if (!strcmp(THP_MODEL, "HTU21")) {
    ht2x.begin();
  } else if (!strcmp(THP_MODEL, "DHT22")) {
    dht.begin(FIRST_THP_SDA);
  } else if (!strcmp(THP_MODEL, "SHT1x")) {
  } else if (!strcmp(THP_MODEL, "DS18B20")) {
    DS18B20.begin();
  }

  yield();
  // TEMP/HUMI/PRESS Sensor setup - END

  // get ESP id
  if (DEVICENAME_AUTO) {
    String ESPmacAddress = WiFi.macAddress();
    ESPmacAddress.replace(":", "");
    ESPmacAddress.toLowerCase();
#ifdef ARDUINO_ARCH_ESP8266
    sprintf(device_name, "Smogly-%06X", ESPmacAddress.c_str());
#elif defined ARDUINO_ARCH_ESP32
    sprintf(device_name, "Smogly-%06X", ESPmacAddress.c_str());
#endif
  } else {
    strncpy(device_name, DEVICENAME, 20);
  }

#ifdef ARDUINO_ARCH_ESP8266
  Serial.print(F("Device name: "));
#elif defined ARDUINO_ARCH_ESP32
  Serial.print(("Device name: "));
#endif
  Serial.println(device_name);

#ifdef ASYNC_WEBSERVER_ON
  DNSServer dns;
  AsyncWiFiManager wifiManager(&server, &dns);
#endif

#ifndef ASYNC_WEBSERVER_ON
  wifiManager.setCountry("US");
#endif

#ifdef ARDUINO_ARCH_ESP8266
  WiFi.hostname(device_name);
#elif defined ARDUINO_ARCH_ESP32
  WiFi.setHostname(device_name);
#endif

  if (wifiManager.autoConnect(device_name)) {
#ifdef ARDUINO_ARCH_ESP8266
    Serial.println(F("connected...yeey :)"));
#elif defined ARDUINO_ARCH_ESP32
    Serial.println(("connected...yeey :)"));
#endif
    //wifiManager.setConfigPortalBlocking(false);
    WiFi.mode(WIFI_STA); // https://github.com/hackerspace-silesia/Smogomierz/issues/47#issue-496810438
#ifdef ARDUINO_ARCH_ESP32
    WiFi.setSleep(false); // https://github.com/espressif/arduino-esp32/issues/962#issuecomment-522899519
#endif
  } else {
#ifdef ARDUINO_ARCH_ESP8266
    Serial.println(F("Configportal running"));
#elif defined ARDUINO_ARCH_ESP32
    Serial.println(("Configportal running"));
#endif
#ifdef ASYNC_WEBSERVER_ON
    wifiManager.startConfigPortal(device_name);
#else
    wifiManager.setConfigPortalBlocking(false);
#endif
  }
#ifdef ASYNC_WEBSERVER_ON
  yield();
#else
  delay(250);
#endif

#ifdef ASYNC_WEBSERVER_ON
#ifdef ARDUINO_ARCH_ESP8266
  Serial.println(F("\nIP Address: ") + String(WiFi.localIP().toString()) + F("\n"));
  Serial.print(F("HTTPServer ready! http://") + String(device_name) + F(".local/\n"));
#elif defined ARDUINO_ARCH_ESP32
  Serial.println(("\nIP Address: ") + String(WiFi.localIP().toString()) + ("\n"));
  Serial.print("HTTPServer ready! http://" + String(device_name) + ".local/\n");
#endif
#endif

  // check update
  unsigned char checkUpdate_x = 0;
  if (checkUpdate(checkUpdate_x) == true) {
    need_update = true;
  } else {
    need_update = false;
  }

  if (MQTT_ON) {
    mqttclient.setServer(MQTT_HOST, MQTT_PORT);
  }

  if (INFLUXDB_ON) {

  }

  //  ASYNC_WebServer config - Start
#ifdef ASYNC_WEBSERVER_ON
  server.on("/", HTTP_GET, handle_root);
  server.on("/config", HTTP_GET, handle_config);
  server.on("/config_device_save", HTTP_GET, handle_config_device_save);
  server.on("/config_device", HTTP_GET, handle_config_device);
  server.on("/config_services_save", HTTP_GET, handle_config_services_save);
  server.on("/config_services", HTTP_GET, handle_config_services);
  server.on("/config_adv_mqtt_save", HTTP_GET, handle_adv_mqtt_config_save);
  server.on("/config_adv_mqtt", HTTP_GET, handle_adv_mqtt_config);
  server.on("/update", HTTP_GET, handle_update);
  server.on("/update_done", HTTP_POST, handle_update_done, handle_update_progress_cb);
  server.on("/api", HTTP_GET, handle_api);
  server.on("/erase_wifi", HTTP_GET, erase_wifi);
  server.on("/restore_config", HTTP_GET, restore_config);
  server.on("/fwupdate", HTTP_GET, fwupdate);
  server.on("/autoupdate_on", HTTP_GET, autoupdate_on);
  server.on("/homekit_reset", HTTP_GET, homekit_reset);
  server.on("/homekit_on", HTTP_GET, homekit_on);
  server.on("/homekit_off", HTTP_GET, homekit_off);
  //server.on("/logout", HTTP_GET, logout);
  server.onNotFound(handle_root);
#else
  //  WebServer config - Start
  WebServer.on("/", HTTP_GET,  handle_root);
  WebServer.on("/config", HTTP_GET, handle_config);
  WebServer.on("/config_device", HTTP_POST, handle_config_device_post);
  WebServer.on("/config_device", HTTP_GET, handle_config_device);
  WebServer.on("/config_services", HTTP_POST, handle_config_services_post);
  WebServer.on("/config_services", HTTP_GET, handle_config_services);
  WebServer.on("/config_adv_mqtt", HTTP_POST, handle_adv_mqtt_config_post);
  WebServer.on("/config_adv_mqtt", HTTP_GET, handle_adv_mqtt_config);
  WebServer.on("/update", HTTP_GET, handle_update);
  WebServer.on("/api", HTTP_GET, handle_api);
  WebServer.on("/erase_wifi", HTTP_GET, erase_wifi);
  WebServer.on("/restore_config", HTTP_GET, restore_config);
  WebServer.on("/fwupdate", HTTP_GET, fwupdate);
  WebServer.on("/autoupdate_on", HTTP_GET, autoupdate_on);

  WebServer.on("/homekit_reset", HTTP_GET, homekit_reset);
  WebServer.on("/homekit_on", HTTP_GET, homekit_on);
  WebServer.on("/homekit_off", HTTP_GET, homekit_off);

  WebServer.onNotFound(handle_root);

#ifdef ARDUINO_ARCH_ESP8266
  httpUpdater.setup(&WebServer, "/update");
#elif defined ARDUINO_ARCH_ESP32
  /*handling uploading firmware file */
  WebServer.on("/update", HTTP_POST, []() {
    WebServer.sendHeader("Connection", "close");
    WebServer.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = WebServer.upload();
    if (upload.status == UPLOAD_FILE_START) {
      //Serial.printf("Update: %s\n", upload.filename.c_str());
      Serial.print(F("Update: ") + String(upload.filename.c_str()) + F("\n"));
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      /* flashing firmware to ESP*/
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        //Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
        Serial.print(F("Update Success: ") + String(upload.totalSize) + F("\nRebooting...\n"));
      } else {
        Update.printError(Serial);
      }
    }
  });
#endif
  //  WebServer Config - End
#endif

  // Check if config.h exist in ESP data folder
#ifdef ASYNC_WEBSERVER_ON

  // https://github.com/me-no-dev/ESPAsyncWebServer/issues/1080#issuecomment-954891157
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "Accept, Content-Type, Authorization");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Credentials", "true");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");

  server.begin();
#else
  WebServer.begin();
#endif

  MDNS.begin(device_name);

  MDNS.addService("http", "tcp", 80);
#ifdef ARDUINO_ARCH_ESP8266
  Serial.print(F("HTTPServer ready! http://") + String(device_name) + F(".local/\n"));
#elif defined ARDUINO_ARCH_ESP32
  Serial.print("HTTPServer ready! http://" + String(device_name) + ".local/\n");
#endif

#ifdef ASYNC_WEBSERVER_ON
  yield();
#else
  delay(300);
#endif

  if (LUFTDATEN_GRAPH_ON) {
    getAPIIDFromLuftdaten();
  }

  // HomeKit -- START
// #ifdef ARDUINO_ARCH_ESP32
//   if (HOMEKIT_SUPPORT) {
// #ifdef ARDUINO_ARCH_ESP8266
//     // disable_extra4k_at_link_time(); // ?????
// #endif
//     // delete old keys!
//     // SPIFFS.remove(pair_file_name);
//     init_hap_storage();
//     set_callback_storage_change(storage_changed);
//     hap_setbase_accessorytype(homekit_accessory_category_sensor);

//     // Setup ID in format "XXXX" (where X is digit or latin capital letter)
//     // Used for pairing using QR code
//     // default = "SMOG"
//     hap_set_device_setupId((char*)"SMOG");

//     // default password = "111-11-111"
//     hap_set_device_password((char*)HOMEKIT_PASSWORD);

//     /// init base properties
//     char homekit_id[12];
//     char homekit_software_version[8];
//     String(device_name).toCharArray(homekit_id, String(device_name).length());
//     String(String(SOFTWAREVERSION).substring(0, 5)).toCharArray(homekit_software_version, 8);

// #ifdef ARDUINO_ARCH_ESP8266
//     hap_initbase_accessory_service("Smogly", "Smogly", homekit_id, "Smogly-ESP8266", homekit_software_version);
// #else
//     hap_initbase_accessory_service("Smogly", "Smogly", homekit_id, "Smogly-ESP32", homekit_software_version);
// #endif

//     homekit_temperature = hap_add_temperature_service("Temperature");
//     homekit_humidity = hap_add_humidity_service("Humidity");

//     homekit_pm10_level = hap_add_air_quality_service("PM10");
//     homekit_pm25_level = hap_add_air_quality_service("PM2.5");

//     pm10_level_characteristic = homekit_service_characteristic_by_type(homekit_pm10_level, HOMEKIT_CHARACTERISTIC_PM10_DENSITY);
//     pm25_level_characteristic = homekit_service_characteristic_by_type(homekit_pm25_level, HOMEKIT_CHARACTERISTIC_PM25_DENSITY);

//     //and finally init HAP
//     hap_init_homekit_server();
//   }
// #endif
  // HomeKit -- END

}

void sendDataToExternalDBs() {

  if (MQTT_ON) {
    if (!mqttclient.connected()) {
      MQTTreconnect();
    }
    mqttclient.loop();
  }

  if (THINGSPEAK_ON) {
    sendDataToThingSpeak(currentTemperature, currentPressure, currentHumidity, averagePM1, averagePM25, averagePM4, averagePM10);
    if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
      Serial.println(F("Sending measurement data to the Thingspeak service!\n"));
#elif defined ARDUINO_ARCH_ESP32
      Serial.println(("Sending measurement data to the Thingspeak service!\n"));
#endif
    }
  }

  if (INFLUXDB_ON) {
    InfluxdbV2 influx(INFLUXDB_HOST, INFLUXDB_PORT);
    if (!strcmp(INFLUXDB_VERSION, "2")) {
      influx.setOrg(INFLUXDB_ORG);
      influx.setBucket(INFLUXDB_BUCKET);
      influx.setToken(INFLUXDB_TOKEN);
    }
    if ( (strcmp( INFLUXDB_USER, "username") != 0 || INFLUXDB_USER != NULL) && (strcmp(INFLUXDB_PASSWORD, "password") != 0 || INFLUXDB_PASSWORD != NULL) ) {
      influx.setDbAuth(INFLUXDB_DATABASE, INFLUXDB_USER, INFLUXDB_PASSWORD);
    } else {
      influx.setDb(INFLUXDB_DATABASE);
    }

    InfluxDataV2 row(device_name);
    if (!strcmp(DUST_MODEL, "PMS7003")) {
      if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
        Serial.println(F("\nMeasurements from PMSx003!\n"));
#elif defined ARDUINO_ARCH_ESP32
        Serial.println(("\nMeasurements from PMSx003!\n"));
#endif
      }
      row.addValue("pm1", averagePM1);
      row.addValue("pm25", averagePM25);
      row.addValue("pm10", averagePM10);
    } else if (!strcmp(DUST_MODEL, "SDS011/21")) {
      if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
        Serial.println(F("\nMeasurements from SDS0x1!\n"));
#elif defined ARDUINO_ARCH_ESP32
        Serial.println(("\nMeasurements from SDS0x1!\n"));
#endif
      }
      row.addValue("pm1", averagePM1);
      row.addValue("pm25", averagePM25);
      row.addValue("pm10", averagePM10);
    } else if (!strcmp(DUST_MODEL, "HPMA115S0")) {
      if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
        Serial.println(F("\nMeasurements from SDS!\n"));
#elif defined ARDUINO_ARCH_ESP32
        Serial.println(("\nMeasurements from SDS!\n"));
#endif
      }
      row.addValue("pm1", averagePM1);
      row.addValue("pm25", averagePM25);
      row.addValue("pm10", averagePM10);
    } else if (!strcmp(DUST_MODEL, "SPS30")) {
      if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
        Serial.println(F("\nMeasurements from SPS30!\n"));
#elif defined ARDUINO_ARCH_ESP32
        Serial.println(("\nMeasurements from SPS30!\n"));
#endif
      }
      row.addValue("pm1", averagePM1);
      row.addValue("pm25", averagePM25);
      row.addValue("pm4", averagePM4);
      row.addValue("pm10", averagePM10);
    } else {
      if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
        Serial.println(F("\nNo measurements from Dust Sensor!\n"));
#elif defined ARDUINO_ARCH_ESP32
        Serial.println(("\nNo measurements from Dust Sensor!\n"));
#endif
      }
    }
    if (!strcmp(THP_MODEL, "BME280")) {
      if (checkBmeStatus() == true) {
        row.addValue("temperature", (currentTemperature));
        row.addValue("pressure", (currentPressure));
        row.addValue("humidity", (currentHumidity));
      } else {
        if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
          Serial.println(F("No measurements from BME280!\n"));
#elif defined ARDUINO_ARCH_ESP32
          Serial.println(("No measurements from BME280!\n"));
#endif
        }
      }
    } else if (!strcmp(THP_MODEL, "HTU21")) {
      if (checkHTU21DStatus() == true) {
        row.addValue("temperature", (currentTemperature));
        row.addValue("humidity", (currentHumidity));
      } else {
        if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
          Serial.println(F("No measurements from HTU21D!\n"));
#elif defined ARDUINO_ARCH_ESP32
          Serial.println(("No measurements from HTU21D!\n"));
#endif
        }
      }
    } else if (!strcmp(THP_MODEL, "BMP280")) {
      if (checkBmpStatus() == true) {
        row.addValue("temperature", (currentTemperature));
        row.addValue("pressure", (currentPressure));
      } else {
        if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
          Serial.println(F("No measurements from BMP280!\n"));
#elif defined ARDUINO_ARCH_ESP32
          Serial.println(("No measurements from BMP280!\n"));
#endif
        }
      }
    } else if (!strcmp(THP_MODEL, "DHT22")) {
      if (checkDHT22Status() == true) {
        row.addValue("temperature", (currentTemperature));
        row.addValue("humidity", (currentHumidity));
      } else {
        if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
          Serial.println(F("No measurements from DHT22!\n"));
#elif defined ARDUINO_ARCH_ESP32
          Serial.println(("No measurements from DHT22!\n"));
#endif
        }
      }
    } else if (!strcmp(THP_MODEL, "SHT1x")) {
      if (checkSHT1xStatus() == true) {
        row.addValue("temperature", (currentTemperature));
        row.addValue("humidity", (currentHumidity));
      } else {
        if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
          Serial.println(F("No measurements from SHT1x!\n"));
#elif defined ARDUINO_ARCH_ESP32
          Serial.println(("No measurements from SHT1x!\n"));
#endif
        }
      }
    } else if (!strcmp(THP_MODEL, "DS18B20")) {
      if (checkDS18B20Status() == true) {
        row.addValue("temperature", (currentTemperature));
      } else {
        if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
          Serial.println(F("No measurements from DS18B20!\n"));
#elif defined ARDUINO_ARCH_ESP32
          Serial.println(("No measurements from DS18B20!\n"));
#endif
        }
      }
    }
    if (influx.write(row)) {
      if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
        Serial.println(F("Data sent to InfluxDB\n"));
#elif defined ARDUINO_ARCH_ESP32
        Serial.println(("Data sent to InfluxDB\n"));
#endif
      }
    } else {
      if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
        Serial.println(F("Error sending data to InfluxDB\n"));
#elif defined ARDUINO_ARCH_ESP32
        Serial.println(("Error sending data to InfluxDB\n"));
#endif
      }
    }
  }

  if (MQTT_ON) {
    char MQTT_DEVICE_NAME[20];
    strcpy(MQTT_DEVICE_NAME, device_name);
    char MQTT_DEVICE_IPADRESS[32];
    (WiFi.localIP().toString()).toCharArray(MQTT_DEVICE_IPADRESS, 32);
    String MQTT_FINAL_TEMP, MQTT_FINAL_HUMI, MQTT_FINAL_PRESS, MQTT_FINAL_PM1, MQTT_FINAL_PM25, MQTT_FINAL_PM10, MQTT_FINAL_AIRQUALITY;
    if (MQTT_DEVICENAME_IN_TOPIC) {
      MQTT_FINAL_TEMP = String(MQTT_DEVICE_NAME) + ("/") + String(MQTT_TOPIC_TEMP);
      MQTT_FINAL_HUMI = String(MQTT_DEVICE_NAME) + ("/") + String(MQTT_TOPIC_HUMI);
      MQTT_FINAL_PRESS = String(MQTT_DEVICE_NAME) + ("/") + String(MQTT_TOPIC_PRESS);
      MQTT_FINAL_PM1 = String(MQTT_DEVICE_NAME) + ("/") + String(MQTT_TOPIC_PM1);
      MQTT_FINAL_PM25 = String(MQTT_DEVICE_NAME) + ("/") + String(MQTT_TOPIC_PM25);
      MQTT_FINAL_PM10 = String(MQTT_DEVICE_NAME) + ("/") + String(MQTT_TOPIC_PM10);
      MQTT_FINAL_AIRQUALITY = String(MQTT_DEVICE_NAME) + ("/") + String(MQTT_TOPIC_AIRQUALITY);
    } else {
      MQTT_FINAL_TEMP = String(MQTT_TOPIC_TEMP);
      MQTT_FINAL_HUMI = String(MQTT_TOPIC_HUMI);
      MQTT_FINAL_PRESS = String(MQTT_TOPIC_PRESS);
      MQTT_FINAL_PM1 = String(MQTT_TOPIC_PM1);
      MQTT_FINAL_PM25 = String(MQTT_TOPIC_PM25);
      MQTT_FINAL_PM10 = String(MQTT_TOPIC_PM10);
      MQTT_FINAL_AIRQUALITY = String(MQTT_TOPIC_AIRQUALITY);
    }
    if (MQTT_IP_IN_TOPIC) {
      MQTT_FINAL_TEMP = String(MQTT_DEVICE_IPADRESS) + ("/") + String(MQTT_FINAL_TEMP);
      MQTT_FINAL_HUMI = String(MQTT_DEVICE_IPADRESS) + ("/") + String(MQTT_FINAL_HUMI);
      MQTT_FINAL_PRESS = String(MQTT_DEVICE_IPADRESS) + ("/") + String(MQTT_FINAL_PRESS);
      MQTT_FINAL_PM1 = String(MQTT_DEVICE_IPADRESS) + ("/") + String(MQTT_FINAL_PM1);
      MQTT_FINAL_PM25 = String(MQTT_DEVICE_IPADRESS) + ("/") + String(MQTT_FINAL_PM25);
      MQTT_FINAL_PM10 = String(MQTT_DEVICE_IPADRESS) + ("/") + String(MQTT_FINAL_PM10);
      MQTT_FINAL_AIRQUALITY = String(MQTT_DEVICE_IPADRESS) + ("/") + String(MQTT_FINAL_AIRQUALITY);
    }
    if (MQTT_SLASH_AT_THE_BEGINNING) {
      MQTT_FINAL_TEMP = ("/") + String(MQTT_FINAL_TEMP);
      MQTT_FINAL_HUMI = ("/") + String(MQTT_FINAL_HUMI);
      MQTT_FINAL_PRESS = ("/") + String(MQTT_FINAL_PRESS);
      MQTT_FINAL_PM1 = ("/") + String(MQTT_FINAL_PM1);
      MQTT_FINAL_PM25 = ("/") + String(MQTT_FINAL_PM25);
      MQTT_FINAL_PM10 = ("/") + String(MQTT_FINAL_PM10);
      MQTT_FINAL_AIRQUALITY = ("/") + String(MQTT_FINAL_AIRQUALITY);
    } else {
      MQTT_FINAL_TEMP = MQTT_FINAL_TEMP;
      MQTT_FINAL_HUMI = MQTT_FINAL_HUMI;
      MQTT_FINAL_PRESS = MQTT_FINAL_PRESS;
      MQTT_FINAL_PM1 = MQTT_FINAL_PM1;
      MQTT_FINAL_PM25 = MQTT_FINAL_PM25;
      MQTT_FINAL_PM10 = MQTT_FINAL_PM10;
      MQTT_FINAL_AIRQUALITY = MQTT_FINAL_AIRQUALITY;
    }

    if (MQTT_SLASH_AT_THE_END) {
      MQTT_FINAL_TEMP = String(MQTT_FINAL_TEMP) + ("/");
      MQTT_FINAL_HUMI = String(MQTT_FINAL_HUMI) + ("/");
      MQTT_FINAL_PRESS = String(MQTT_FINAL_PRESS) + ("/");
      MQTT_FINAL_PM1 = String(MQTT_FINAL_PM1) + ("/");
      MQTT_FINAL_PM25 = String(MQTT_FINAL_PM25) + ("/");
      MQTT_FINAL_PM10 = String(MQTT_FINAL_PM10) + ("/");
      MQTT_FINAL_AIRQUALITY = String(MQTT_FINAL_AIRQUALITY) + ("/");
    }
    if (strcmp(DUST_MODEL, "Non")) {

      mqttclient.publish((MQTT_FINAL_PM1).c_str(), String(averagePM1).c_str(), true);
      mqttclient.publish((MQTT_FINAL_PM25).c_str(), String(averagePM25).c_str(), true);
      mqttclient.publish((MQTT_FINAL_PM10).c_str(), String(averagePM10).c_str(), true);

      if (averagePM25 <= 10) {
        mqttclient.publish((MQTT_FINAL_AIRQUALITY).c_str(), "EXCELLENT", true);
      } else if (averagePM25 > 10 && averagePM25 <= 20) {
        mqttclient.publish((MQTT_FINAL_AIRQUALITY).c_str(), "GOOD", true);
      } else if (averagePM25 > 20 && averagePM25 <= 25) {
        mqttclient.publish((MQTT_FINAL_AIRQUALITY).c_str(), "FAIR", true);
      } else if (averagePM25 > 25 && averagePM25 <= 50) {
        mqttclient.publish((MQTT_FINAL_AIRQUALITY).c_str(), "INFERIOR", true);
      } else if (averagePM25 > 50) {
        mqttclient.publish((MQTT_FINAL_AIRQUALITY).c_str(), "POOR", true);
      } else {
        mqttclient.publish((MQTT_FINAL_AIRQUALITY).c_str(), "UNKNOWN", true);
      }
    }

    if (!strcmp(THP_MODEL, "BME280")) {
      if (checkBmeStatus() == true) {
        mqttclient.publish((MQTT_FINAL_TEMP).c_str(), String(currentTemperature).c_str(), true);
        mqttclient.publish((MQTT_FINAL_HUMI).c_str(), String(currentHumidity).c_str(), true);
        mqttclient.publish((MQTT_FINAL_PRESS).c_str(), String(currentPressure).c_str(), true);
      } else {
        if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
          Serial.println(F("No measurements from BME280!\n"));
#elif defined ARDUINO_ARCH_ESP32
          Serial.println(("No measurements from BME280!\n"));
#endif
        }
      }
    }

    if (!strcmp(THP_MODEL, "BMP280")) {
      if (checkBmpStatus() == true) {
        mqttclient.publish((MQTT_FINAL_TEMP).c_str(), String(currentTemperature).c_str(), true);
        mqttclient.publish((MQTT_FINAL_PRESS).c_str(), String(currentPressure).c_str(), true);
      } else {

        if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
          Serial.println(F("No measurements from BMP280!\n"));
#elif defined ARDUINO_ARCH_ESP32
          Serial.println(("No measurements from BMP280!\n"));
#endif
        }
      }
    }

    if (!strcmp(THP_MODEL, "HTU21")) {
      if (checkHTU21DStatus() == true) {
        mqttclient.publish((MQTT_FINAL_TEMP).c_str(), String(currentTemperature).c_str(), true);
        mqttclient.publish((MQTT_FINAL_HUMI).c_str(), String(currentHumidity).c_str(), true);
      } else {
        if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
          Serial.println(F("No measurements from HTU21!\n"));
#elif defined ARDUINO_ARCH_ESP32
          Serial.println(("No measurements from HTU21!\n"));
#endif
        }
      }
    }

    if (!strcmp(THP_MODEL, "DHT22")) {
      if (checkDHT22Status() == true) {
        mqttclient.publish((MQTT_FINAL_TEMP).c_str(), String(currentTemperature).c_str(), true);
        mqttclient.publish((MQTT_FINAL_HUMI).c_str(), String(currentHumidity).c_str(), true);
      } else {
        if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
          Serial.println(F("No measurements from DHT22!\n"));
#elif defined ARDUINO_ARCH_ESP32
          Serial.println(("No measurements from DHT22!\n"));
#endif
        }
      }
    }

    if (!strcmp(THP_MODEL, "SHT1x")) {
      if (checkDHT22Status() == true) {
        mqttclient.publish((MQTT_FINAL_TEMP).c_str(), String(currentTemperature).c_str(), true);
        mqttclient.publish((MQTT_FINAL_HUMI).c_str(), String(currentHumidity).c_str(), true);
      } else {
        if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
          Serial.println(F("No measurements from SHT1x!\n"));
#elif defined ARDUINO_ARCH_ESP32
          Serial.println(("No measurements from SHT1x!\n"));
#endif
        }
      }
    }

    if (!strcmp(THP_MODEL, "DS18B20")) {
      if (checkDS18B20Status() == true) {
        mqttclient.publish((MQTT_FINAL_TEMP).c_str(), String(currentTemperature).c_str(), true);
      } else {
        if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
          Serial.println(F("No measurements from DS18B20!\n"));
#elif defined ARDUINO_ARCH_ESP32
          Serial.println(("No measurements from DS18B20!\n"));
#endif
        }
      }
    }

    //if (DEEPSLEEP_ON == true) {
    mqttclient.disconnect();
    //}
  }

}


void updateTHPMeasurements () {
    currentTemperature = takeTHPMeasurements().temperature;
    currentHumidity = takeTHPMeasurements().humidity;
    currentHumidity = takeTHPMeasurements().pressure;
}

void sendDataToExternalServices() {

  if (LUFTDATEN_ON) {
    sendDataToLuftdaten(currentTemperature, currentPressure, currentHumidity, averagePM1, averagePM25, averagePM4, averagePM10);
    if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
      Serial.println(F("Sending measurement data to the LuftDaten service!\n"));
#elif defined ARDUINO_ARCH_ESP32
      Serial.println(("Sending measurement data to the LuftDaten service!\n"));
#endif
    }
  }

#ifdef ARDUINO_ARCH_ESP32
  if (AIRMONITOR_ON) {
    sendDataToAirMonitor(currentTemperature, currentPressure, currentHumidity, averagePM1, averagePM25, averagePM4, averagePM10);
    if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
      Serial.println(F("Sending measurement data to the AirMonitor service!\n"));
#elif defined ARDUINO_ARCH_ESP32
      Serial.println(("Sending measurement data to the AirMonitor service!\n"));
#endif
    }
  }
#endif

#ifndef DISABLE_SMOGLIST
  if (SMOGLIST_ON) {
    sendDataToSmoglist(currentTemperature, currentPressure, currentHumidity, averagePM1, averagePM25, averagePM4, averagePM10);
    if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
      Serial.println(F("Sending measurement data to the Smoglist service!\n"));
#elif defined ARDUINO_ARCH_ESP32
      Serial.println(("Sending measurement data to the Smoglist service!\n"));
#endif
    }
  }
#endif

  if (AQI_ECO_ON) {
    sendDataToAqiEco(currentTemperature, currentPressure, currentHumidity, averagePM1, averagePM25, averagePM4, averagePM10);
    if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
      Serial.println(F("Sending measurement data to the aqi.eco service!\n"));
#elif defined ARDUINO_ARCH_ESP32
      Serial.println(("Sending measurement data to the aqi.eco service!\n"));
#endif
    }
  }

}

void loop() {
  /*
    Serial.print(F("========================================\n"));
    Serial.println(F("Free Heap: " + String(ESP.getFreeHeap())));
    Serial.print(F("========================================\n"));
  */

  if (need_update == true && AUTOUPDATE_ON) {
    for (int i = 0; i < 5 ; i++) {
      unsigned char x = 0;
      doUpdate(x);

#ifdef ASYNC_WEBSERVER_ON
      yield();
      delay(1000);

#else
      delay(1000);
#endif

    }
  }

  yield();

  pm_calibration();

  // DUST SENSOR refresh data - START
#ifdef DUSTSENSOR_PMS5003_7003_BME280_0x76 or DUSTSENSOR_PMS5003_7003_BME280_0x77
  if (!strcmp(DUST_MODEL, "PMS7003")) {
    pms.read(data);
  }
#elif defined DUSTSENSOR_SDS011_21
#ifdef ARDUINO_ARCH_ESP8266
  PmResult SDSdata = sds.queryPm();
#endif
#elif defined DUSTSENSOR_HPMA115S0
#elif defined DUSTSENSOR_SPS30
  //read_sps30_data();
#else // If no dust sensor has been defined - use DUSTSENSOR_PMS5003_7003_BME280_0x76
  if (!strcmp(DUST_MODEL, "PMS7003")) {
    pms.read(data);
  }
#endif
  // DUST SENSOR refresh data - END

#ifndef ASYNC_WEBSERVER_ON
  WebServer.handleClient();
#endif

#ifdef ARDUINO_ARCH_ESP8266
  MDNS.update();
#endif

  if (strcmp(DUST_MODEL, "Non")) {
    unsigned int current_DUST_Millis = millis();
    if (FREQUENTMEASUREMENT == true ) {
      if (current_DUST_Millis - previous_DUST_Millis >= DUST_interval) {
        if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
          Serial.println(F("\nFREQUENT MEASUREMENT Mode!"));
#elif defined ARDUINO_ARCH_ESP32
          Serial.println(("\nFREQUENT MEASUREMENT Mode!"));
#endif
        }
        takeNormalnPMMeasurements();
        previous_DUST_Millis = millis();
      }
    }
    if (DEEPSLEEP_ON == true) {
      if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
        Serial.println(F("\nDeepSleep Mode!"));
#elif defined ARDUINO_ARCH_ESP32
        Serial.println(("\nDeepSleep Mode!"));
#endif
      }
      takeSleepPMMeasurements();
      yield();

      if (LUFTDATEN_ON or AQI_ECO_ON or AIRMONITOR_ON or SMOGLIST_ON) {
        
        updateTHPMeasurements();
        sendDataToExternalServices();
      }
      if (THINGSPEAK_ON or INFLUXDB_ON or MQTT_ON) {
        updateTHPMeasurements();
        sendDataToExternalDBs();
      }

#ifdef ARDUINO_ARCH_ESP8266
      Serial.println(F("Going into deep sleep for ") + String(SENDING_FREQUENCY) + F(" minutes!"));
      Serial.flush();
      ESP.deepSleep(SENDING_FREQUENCY * 60 * 1000000); // *1000000 - secunds

      yield();

#elif defined ARDUINO_ARCH_ESP32
      Serial.println(("Going to sleep now"));
      Serial.flush();
      esp_deep_sleep_start();
#endif

    } else {
      if (current_DUST_Millis - previous_DUST_Millis >= DUST_interval) {
        if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
          Serial.println(F("\nNormal Mode!"));
#elif defined ARDUINO_ARCH_ESP32
          Serial.println(("\nNormal Mode!"));
#endif
        }
        takeSleepPMMeasurements();
        previous_DUST_Millis = millis();
      }
    }
  } else {
    if (DEEPSLEEP_ON == true) {
#ifdef ARDUINO_ARCH_ESP8266
      Serial.println(F("\nDeepSleep Mode!\n"));
#elif defined ARDUINO_ARCH_ESP32
      Serial.println(("\nDeepSleep Mode!\n"));
#endif
      unsigned int current_2sec_Millis = millis();
      previous_2sec_Millis = millis();
      while (previous_2sec_Millis - current_2sec_Millis <= TwoSec_interval * 10) {
#ifndef ASYNC_WEBSERVER_ON
        WebServer.handleClient();
#endif
        previous_2sec_Millis = millis();
      }
      if (LUFTDATEN_ON or AQI_ECO_ON or AIRMONITOR_ON or SMOGLIST_ON) {
        updateTHPMeasurements();
        sendDataToExternalServices();
      }
      if (THINGSPEAK_ON or INFLUXDB_ON or MQTT_ON) {
        updateTHPMeasurements();
        sendDataToExternalDBs();
      }

      yield();

#ifdef ARDUINO_ARCH_ESP8266
      Serial.println(F("Going into deep sleep for ") + String(SENDING_FREQUENCY) + F(" minutes!"));
      Serial.flush();
      ESP.deepSleep(SENDING_FREQUENCY * 60 * 1000000); // *1000000 - secunds
      yield();
#elif defined ARDUINO_ARCH_ESP32
      Serial.println(("Going to sleep now"));
      Serial.flush();
      esp_deep_sleep_start();
#endif

    }
  }

  if (AIRMONITOR_ON) {
    // Serial.println("SENDING_FREQUENCY_AIRMONITOR_interval: " + String(SENDING_FREQUENCY_AIRMONITOR_interval));
    // Serial.println("previous_SENDING_FREQUENCY_AIRMONITOR_Millis: " + String(previous_SENDING_FREQUENCY_AIRMONITOR_Millis));

    unsigned int current_SENDING_FREQUENCY_AIRMONITOR_Millis = millis();
    // Serial.println("current_SENDING_FREQUENCY_AIRMONITOR_Millis: " + String(current_SENDING_FREQUENCY_AIRMONITOR_Millis));

    if (current_SENDING_FREQUENCY_AIRMONITOR_Millis - previous_SENDING_FREQUENCY_AIRMONITOR_Millis >= SENDING_FREQUENCY_AIRMONITOR_interval) {
        updateTHPMeasurements();
      // Serial.println("SEND DATA TO AIRMONITOR");
      sendDataToExternalServices();
      previous_SENDING_FREQUENCY_AIRMONITOR_Millis = millis();
    }
  }

  if (LUFTDATEN_ON or AQI_ECO_ON or SMOGLIST_ON) {
    unsigned int current_SENDING_FREQUENCY_Millis = millis();
    if (current_SENDING_FREQUENCY_Millis - previous_SENDING_FREQUENCY_Millis >= SENDING_FREQUENCY_interval) {
        updateTHPMeasurements();
      sendDataToExternalServices();
      previous_SENDING_FREQUENCY_Millis = millis();
    }
  }

  if (THINGSPEAK_ON or INFLUXDB_ON or MQTT_ON) {
    unsigned int current_SENDING_DB_FREQUENCY_Millis = millis();
    if (current_SENDING_DB_FREQUENCY_Millis - previous_SENDING_DB_FREQUENCY_Millis >= SENDING_DB_FREQUENCY_interval) {
        updateTHPMeasurements();
      sendDataToExternalDBs();
      previous_SENDING_DB_FREQUENCY_Millis = millis();
    }
  }

  unsigned int current_REBOOT_Millis = millis();
  if (current_REBOOT_Millis - previous_REBOOT_Millis >= REBOOT_interval) {
#ifdef ARDUINO_ARCH_ESP8266
    Serial.println(F("autoreboot..."));
#elif defined ARDUINO_ARCH_ESP32
    Serial.println(("autoreboot..."));
#endif
    delay(1000);
    previous_REBOOT_Millis = millis();

#ifdef ARDUINO_ARCH_ESP8266
    ESP.reset();
#elif defined ARDUINO_ARCH_ESP32
    ESP.restart();
#endif

    delay(5000);
  }

  /*
    unsigned int current_SENDING_FREQUENCY_Millis = millis();
    if (current_SENDING_FREQUENCY_Millis - previous_SENDING_FREQUENCY_Millis >= SENDING_FREQUENCY_interval) {
    #ifdef ARDUINO_ARCH_ESP32
      if (HOMEKIT_SUPPORT) {
        homekit_DeviceData.homekit_temperature = float(random(-11.00, 45));
        homekit_DeviceData.homekit_humidity = float(random(0.0, 99));
        homekit_DeviceData.homekit_pm10_level = int(random(0, 3000));
        homekit_DeviceData.homekit_pm25_level = int(random(0, 2000));
        notify_hap();
      }
    #endif
      previous_SENDING_FREQUENCY_Millis = millis();
    }
  */

} // loop() - END





String addSlash(String receivedString, bool frontSlash, bool backSlash) {
  if (frontSlash) {
    if (String(receivedString.charAt(0)) != ("/")) {
      receivedString = "/" + receivedString;
    }
  }
  if (backSlash) {
    if (String(receivedString.charAt(receivedString.length() - 1)) != ("/")) {
      receivedString = receivedString + ("/");
    }
  }
  return receivedString;
}














// HomeKit -- START
// #ifdef ARDUINO_ARCH_ESP32
// void init_hap_storage() {
// #ifdef ARDUINO_ARCH_ESP8266
//   Serial.print(F("init_hap_storage"));
// #elif defined ARDUINO_ARCH_ESP32
//   Serial.print(("init_hap_storage"));
// #endif

// #ifdef ARDUINO_ARCH_ESP32
// #define FORMAT_SPIFFS_IF_FAILED true
//   if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
//     Serial.println(("SPIFFS Mount Failed"));
//     return;
//   }
// #endif



//   if (!fsDAT) {
// #ifdef ARDUINO_ARCH_ESP8266
//     Serial.println(F("Failed to read pair.dat"));
// #elif defined ARDUINO_ARCH_ESP32
//     Serial.println(("Failed to read pair.dat"));
// #endif
//     return;
//   }
//   int size = hap_get_storage_size_ex();
//   char* buf = new char[size];
//   memset(buf, 0xff, size);
//   int readed = fsDAT.readBytes(buf, size);
//   //Serial.print(F("Readed bytes ->"));
//   //Serial.println(readed);
//   hap_init_storage_ex(buf, size);
//   fsDAT.close();
//   delete []buf;

// }

void storage_changed(char * szstorage, int size) {
  SPIFFS.remove(pair_file_name);
#ifdef ARDUINO_ARCH_ESP8266
  File fsDAT = SPIFFS.open(pair_file_name, "w+");
#elif defined ARDUINO_ARCH_ESP32
  File fsDAT = SPIFFS.open(pair_file_name, FILE_WRITE);
#endif
  if (!fsDAT) {
#ifdef ARDUINO_ARCH_ESP8266
    Serial.println(F("Failed to open pair.dat"));
#elif defined ARDUINO_ARCH_ESP32
    Serial.println(("Failed to open pair.dat"));
#endif
    return;
  }
  fsDAT.write((uint8_t*)szstorage, size);

  fsDAT.close();
}

// HomeKit -- START
// void notify_hap() {
//   if (homekit_temperature) {
//     homekit_characteristic_t * ch_temp = homekit_service_characteristic_by_type(homekit_temperature, HOMEKIT_CHARACTERISTIC_CURRENT_TEMPERATURE);
//     if (ch_temp && !isnan(homekit_DeviceData.homekit_temperature) &&  ch_temp->value.float_value != homekit_DeviceData.homekit_temperature ) {
//       ch_temp->value.float_value = homekit_DeviceData.homekit_temperature;
//       homekit_characteristic_notify(ch_temp, ch_temp->value);
//     }
//   }

//   if (homekit_humidity) {
//     homekit_characteristic_t * ch_hum = homekit_service_characteristic_by_type(homekit_humidity, HOMEKIT_CHARACTERISTIC_CURRENT_RELATIVE_HUMIDITY);
//     if (ch_hum && !isnan(homekit_DeviceData.homekit_humidity) && ch_hum->value.float_value != homekit_DeviceData.homekit_humidity) {
//       ch_hum->value.float_value = homekit_DeviceData.homekit_humidity;
//       homekit_characteristic_notify(ch_hum, ch_hum->value);
//     }
//   }

//   if (homekit_pm10_level) {
//     HAP_NOTIFY_CHANGES(float, pm10_level_characteristic, homekit_DeviceData.homekit_pm10_level, 0.0)
//     homekit_characteristic_t* hc_homekit_pm10_level = homekit_service_characteristic_by_type(homekit_pm10_level, HOMEKIT_CHARACTERISTIC_PM10_DENSITY);
//     if ( hc_homekit_pm10_level) {
//       uint8_t air_quality_pm10 = pm10_air_quality_level(homekit_DeviceData.homekit_pm10_level, (uint8_t)(* hc_homekit_pm10_level->min_value) + 1, (uint8_t)(* hc_homekit_pm10_level->max_value));
//       // Serial.println(F("Noify level:") + String(air_quality_pm10));
//       HAP_NOTIFY_CHANGES(int, hc_homekit_pm10_level, air_quality_pm10, 0)
//     }
//   }

//   if (homekit_pm25_level) {
//     HAP_NOTIFY_CHANGES(float, pm25_level_characteristic, homekit_DeviceData.homekit_pm25_level, 0.0)
//     homekit_characteristic_t* hc_homekit_pm25_level = homekit_service_characteristic_by_type(homekit_pm25_level, HOMEKIT_CHARACTERISTIC_PM25_DENSITY);
//     if ( hc_homekit_pm25_level) {
//       uint8_t air_quality_pm25 = pm25_air_quality_level(homekit_DeviceData.homekit_pm25_level, (uint8_t)(* hc_homekit_pm25_level->min_value) + 1, (uint8_t)(* hc_homekit_pm25_level->max_value));
//       // Serial.println(F("Noify level:") + String(air_quality_pm25));
//       HAP_NOTIFY_CHANGES(int, hc_homekit_pm25_level, air_quality_pm25, 0)
//     }
//   }
// }

#define PM25_RANGE_EXCELLENT_LEVEL 20.0
#define PM25_RANGE_POOR_LEVEL 100.0
uint8_t pm25_air_quality_level(float input_value, uint8_t min, uint8_t max) {
  if (input_value < PM25_RANGE_EXCELLENT_LEVEL)
    return min;
  if (input_value > PM25_RANGE_POOR_LEVEL)
    return max;
  return ((int)input_value) / ((PM25_RANGE_POOR_LEVEL - PM25_RANGE_EXCELLENT_LEVEL) / (float)(max - min));
}

#define PM10_RANGE_EXCELLENT_LEVEL 50.0
#define PM10_RANGE_POOR_LEVEL 150.0
uint8_t pm10_air_quality_level(float input_value, uint8_t min, uint8_t max) {
  if (input_value < PM10_RANGE_EXCELLENT_LEVEL)
    return min;
  if (input_value > PM10_RANGE_POOR_LEVEL)
    return max;
  return ((int)input_value) / ((PM10_RANGE_POOR_LEVEL - PM10_RANGE_EXCELLENT_LEVEL) / (float)(max - min));
}
// #endif
// HomeKit -- END