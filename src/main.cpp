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
#include <ESPAsyncWiFiManager.h> // https://github.com/alanswx/ESPAsyncWiFiManager // 5.11.2021

// #include "../lib/smogly_spiffs.hpp"
#include "defaultConfig.h"
// #include "../lib/defaultConfig.h"

// #include "../lib/autoupdate.h"

// #ifndef DISABLE_SMOGLIST
// #include "../lib/services/smoglist.h"
// #endif

//        it would be nice to update the InfluxDB library to
// #include "src/services/InfluxDB/InfluxDbClient.h" // https://github.com/tobiasschuerg/InfluxDB-Client-for-Arduino

#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>


#include "Dust.h"
#include "TemperatureHumidityPressure.h"

#include "../lib/services/luftdaten.h"

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <Update.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <time.h>
#include <HardwareSerial.h>

#include <Wire.h>


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

TemperatureHumidityPressureSensor thpSensor;

static float currentTemperature, currentHumidity, currentPressure = 0;
// float currentTemperature_THP1, currentHumidity_THP1, currentPressure_THP1 = 0;
// float currentTemperature_THP2, currentHumidity_THP2, currentPressure_THP2 = 0;

static bool need_update = false;
char SERVERSOFTWAREVERSION[32] = "";
char CURRENTSOFTWAREVERSION[32] = "";

AsyncWebServer server(80);


WiFiClient espClient;

// https://github.com/Yurik72/ESPHap
// HomeKit -- START
#ifdef ARDUINO_ARCH_ESP32
#include <SPIFFS.h>
#endif

String pair_file_name = "/homekit_pair.dat";



#ifndef ASYNC_WEBSERVER_ON
WiFiManager wifiManager;
#endif





  File fsDAT = SPIFFS.open(pair_file_name, FILE_READ);





// check TEMP/HUMI/PRESS Sensor - END

void minutesToSeconds() {
  DUST_interval = 1000; // 1 second
  SENDING_FREQUENCY_interval = 1000;
  SENDING_DB_FREQUENCY_interval = 1000;
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
#include "../lib/smogly_asyncwebserver.hpp"


static String handle_root_processor(const String& var)
{
  // Serial.println(F("var: ") + var);
  String message;
  message = "";

  if (var == F("{Language}")) {
    message += String(TEXT_LANG);
  }

  if (var == F("{WEB_PAGE_CSS}")) {
    message += String(WEB_PAGE_HEADER_CSS);
  }

  if (var == F("{SMOGLY_LOGO_URL}")) {
    message += String(SMOGLY_LOGO_URL);
  }

  if (var == F("{CurrentPageTitle}")) {
    message += String(TEXT_INDEX_PAGE);
  }
  if (var == F("{IndexPageTitle}")) {
    message += String(TEXT_INDEX_PAGE);
  }
  if (var == F("{ConfigPageTitle}")) {
    message += String(TEXT_CONFIG_PAGE);
  }
  if (var == F("{UpdatePageTitle}")) {
    message += String(TEXT_UPDATE_PAGE);
  }

  if (!AUTOUPDATE_ON) {
    if (need_update) {
      if (var == F("{WEB_UPDATE_INFO_WARNING}")) {
        message += String(WEB_UPDATE_INFO_WARNING);
      }

      if (var == F("{TEXT_FWUPDATEAVALIBLE}")) {
        message += String(TEXT_FWUPDATEAVALIBLE);
      }
      if (var == F("{MANUALUPDATEBUTTON}")) {
        message += "";
      }

      if (var == F("{FWUPDATEBUTTON}")) {
        message += String(WEB_UPDATE_BUTTON_FWUPDATE);
      }
      if (var == F("{TEXT_FWUPDATEBUTTON}")) {
        message += String(TEXT_FWUPDATEBUTTON);
      }

      if (var == F("{AUTOUPDATEONBUTTON}")) {
        message += String(WEB_UPDATE_BUTTON_AUTOUPDATEON);
      }
      if (var == F("{TEXT_AUTOUPDATEONBUTTON}")) {
        message += String(TEXT_AUTOUPDATEONBUTTON);
      }

      if (var == F("{TEXT_AUTOUPDATEWARNING}")) {
        message += String(TEXT_AUTOUPDATEWARNING);
      }
      if (var == F("{TEXT_FWUPDATEBUTTON}")) {
        message += String(TEXT_FWUPDATEBUTTON);
      }

    }
    if (var == F("{WEB_UPDATE_INFO_WARNING}")) {
      message += "";
    }
  } else {
    if (var == F("{WEB_UPDATE_INFO_WARNING}")) {
      message += "";
    }
  }

  if (!strcmp(THP_MODEL, "Non")) {
    if (var == F("{WEB_ROOT_PAGE_MEASUREMENTS_THP1")) {
      message += "";
    }
  } else {
    if (var == F("{WEB_ROOT_PAGE_MEASUREMENTS_THP1")) {
      // takeTHPMeasurements();
      message += String(WEB_ROOT_PAGE_MEASUREMENTS_THP1);
      message.replace(F("{TEXT_WEATHER}"), String(TEXT_WEATHER));

      if (!strcmp(THP_MODEL, "BME280")) {
        if (thpSensor.getStatus()) {
            message.replace(F("{TEXT_TEMPERATURE}"), String(TEXT_TEMPERATURE));
            message.replace(F("{TEXT_HUMIDITY}"), String(TEXT_HUMIDITY));
            message.replace(F("{TEXT_PRESSURE}"), String(TEXT_PRESSURE));
            message.replace(F("{TEXT_DEWPOINT}"), String(TEXT_DEWPOINT));

            message.replace(F("{Temperature}"), String(int(currentTemperature)));
            message.replace(F("{Pressure}"), String(int(currentPressure)));
            message.replace(F("{Humidity}"), String(int(currentHumidity)));
            message.replace(F("{Dewpoint}"), String(int(pow((currentHumidity) / 100, 0.125) * (112 + 0.9 * (currentTemperature)) + 0.1 * (currentTemperature) - 112)));
        } else {
          message.replace(F("{TEXT_TEMPERATURE}: {Temperature} °C"), "");
          message.replace(F("{TEXT_HUMIDITY}: {Humidity} %"), "");
          message.replace(F("{TEXT_PRESSURE}: {Pressure} hPa"), "");
          message.replace(F("{TEXT_DEWPOINT}: {Dewpoint} °C"), "");
        }
      } 

    }
  }

  if (strcmp(DUST_MODEL, "Non")) {
    if (var == F("{WEB_ROOT_PAGE_MEASUREMENTS_AIR}")) {
      message += String(WEB_ROOT_PAGE_MEASUREMENTS_AIR);
      message.replace(F("{TEXT_AIRPOLLUTION}"), String(TEXT_AIRPOLLUTION));

      if (DISPLAY_PM1) {
        message.replace(F("{averagePM1}"), String(averagePM1));
      } else {
        message.replace(F("PM1: {averagePM1} µg/m³"), "");
      }

      if (averagePM25 <= 10) {
        message.replace(F("{colorAveragePM25}"), F("<font color='#61EEE4'>"));
      } else if (averagePM25 > 10 && averagePM25 <= 20) {
        message.replace(F("{colorAveragePM25}"), F("<font color='#5BCAAA'>"));
      } else if (averagePM25 > 20 && averagePM25 <= 25) {
        message.replace(F("{colorAveragePM25}"), F("<font color='#EEE25D'>"));
      } else if (averagePM25 > 25 && averagePM25 <= 50) {
        message.replace(F("{colorAveragePM25}"), F("<font color='#F95459'>"));
      } else if (averagePM25 > 50) {
        message.replace(F("{colorAveragePM25}"), F("<font color='#920736'>"));
      } else {
        message.replace(F("{colorAveragePM25}"), F("<font>"));
      }

      message.replace(F("{averagePM25}"), String(averagePM25) + F("</font>"));

      if (averagePM10 <= 20) {
        message.replace(F("{colorAveragePM10}"), F("<font color='#61EEE4'>"));
      } else if (averagePM10 > 20 && averagePM10 <= 35) {
        message.replace(F("{colorAveragePM10}"), F("<font color='#5BCAAA'>"));
      } else if (averagePM10 > 35 && averagePM10 <= 50) {
        message.replace(F("{colorAveragePM10}"), F("<font color='#EEE25D'>"));
      } else if (averagePM10 > 50 && averagePM10 <= 100) {
        message.replace(F("{colorAveragePM10}"), F("<font color='#F95459'>"));
      } else if (averagePM10 > 100) {
        message.replace(F("{colorAveragePM10}"), F("<font color='#920736'>"));
      } else {
        message.replace(F("{colorAveragePM10}"), F("<font>"));
      }
      message.replace(F("{averagePM10}"), String(averagePM10) + F("</font>"));
    }
  } else {
    if (var == F("{WEB_ROOT_PAGE_MEASUREMENTS_AIR}")) {
      message += "";
    }
  }

  if (AIRMONITOR_GRAPH_ON) {
    if (var == F("{WEB_ROOT_PAGE_AIRMONITOR_GRAPH}")) {
      message += String(WEB_ROOT_PAGE_AIRMONITOR_GRAPH);
      message.replace(F("{LATITUDE}"), String(LATITUDE));
      message.replace(F("{LONGITUDE}"), String(LONGITUDE));
    }
  } else {
    if (var == F("{WEB_ROOT_PAGE_AIRMONITOR_GRAPH}")) {
      message += "";
    }
  }
  
  if (LUFTDATEN_GRAPH_ON) {
      if (var == F("{WEB_ROOT_PAGE_LUFTDATEN_GRAPH}")) {
          message += String(WEB_ROOT_PAGE_LUFTDATEN_GRAPH);
          message.replace(F("{NODE_LUFTDATEN_ID}"), String(LUFTDATEN_APIID));
      }
  } else {
    if (var == F("{WEB_ROOT_PAGE_LUFTDATEN_GRAPH}")) {
      message += "";
    }
  }

  if (THINGSPEAK_GRAPH_ON) {
    if (var == F("{WEB_ROOT_PAGE_THINGSPEAK_GRAPH}")) {
      message += String(WEB_ROOT_PAGE_THINGSPEAK_GRAPH);
      message.replace(F("{THINGSPEAK_CHANNEL_ID}"), String(THINGSPEAK_CHANNEL_ID));
      message.replace(F("{THINGSPEAK_READ_API_KEY}"), String(THINGSPEAK_READ_API_KEY));
    }
  } else {
    if (var == F("{WEB_ROOT_PAGE_THINGSPEAK_GRAPH}")) {
      message += "";
    }
  }

  return message;
  message = "";
}

static void handle_root(AsyncWebServerRequest *request) {
  if (DEBUG) {
    Serial.print(F("sizeof(WEB_ROOT_PAGE_ALL): "));
    Serial.println(sizeof(WEB_ROOT_PAGE_ALL)); // sizeof(WEB_ROOT_PAGE_ALL): ~2255
    Serial.print(F("\n"));
  }

  // request->send_P(200, "text/html", WEB_ROOT_PAGE_ALL, handle_root_processor);
}


// static void handle_api(AsyncWebServerRequest *request) {
//   String message;
//   StaticJsonDocument<800> jsonBuffer;
//   JsonObject json = jsonBuffer.to<JsonObject>();

//   json[F("device_name")] = device_name;
//   if (strcmp(DUST_MODEL, "Non")) {
//     json[F("pm1")] = averagePM1;
//     json[F("pm25")] = averagePM25;
//     if (!strcmp(DUST_MODEL, "SPS30")) {
//       json[F("pm4")] = averagePM4;
//     }
//     json[F("pm10")] = averagePM10;
//   }
//   if (strcmp(THP_MODEL, "Non")) {
//     takeTHPMeasurements();
//   }
//   if (!strcmp(THP_MODEL, "BME280")) {
//     if (checkBmeStatus()) {
//       json[F("temperature")] = float(currentTemperature);
//       json[F("pressure")] = int(currentPressure);
//       json[F("humidity")] = int(currentHumidity);
//       json[F("dewpoint")] = float(pow((currentHumidity) / 100, 0.125) * (112 + 0.9 * (currentTemperature)) + 0.1 * (currentTemperature) - 112);
//     }
//   }
//   if (!strcmp(THP_MODEL, "BMP280")) {
//     if (checkBmpStatus()) {
//       json[F("temperature")] = float(currentTemperature);
//       json[F("pressure")] = int(currentPressure);
//     }
//   }
//   if (!strcmp(THP_MODEL, "HTU21")) {
//     if (checkHTU21DStatus()) {
//       json[F("temperature")] = float(currentTemperature);
//       json[F("humidity")] = int(currentHumidity);
//       json[F("dewpoint")] = float(pow((currentHumidity) / 100, 0.125) * (112 + 0.9 * (currentTemperature)) + 0.1 * (currentTemperature) - 112);
//     }
//   }
//   if (!strcmp(THP_MODEL, "DHT22")) {
//     if (checkDHT22Status()) {
//       json[F("temperature")] = float(currentTemperature);
//       json[F("humidity")] = int(currentHumidity);
//       json[F("dewpoint")] = float(pow((currentHumidity) / 100, 0.125) * (112 + 0.9 * (currentTemperature)) + 0.1 * (currentTemperature) - 112);
//     }
//   }
//   if (!strcmp(THP_MODEL, "SHT1x")) {
//     if (checkSHT1xStatus()) {
//       json[F("temperature")] = float(currentTemperature);
//       json[F("humidity")] = int(currentHumidity);
//       json[F("dewpoint")] = float(pow((currentHumidity) / 100, 0.125) * (112 + 0.9 * (currentTemperature)) + 0.1 * (currentTemperature) - 112);
//     }
//   }

//   serializeJsonPretty(json, message);
//   //WebServer.send(200, "text/json", message);
//   request->send(200, "text/json", message);
// }

void setup() {
  Serial.begin(115200);
  yield();

  // fs_setup();
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
  // loadtranslation(SELECTED_LANGUAGE);
#endif
  yield();

  set_I2C_PINS(CONFIG_FIRST_THP_SDA, 1);
  set_I2C_PINS(CONFIG_FIRST_THP_SCL, 2);

  set_I2C_PINS(CONFIG_SECOND_THP_SDA, 3);
  set_I2C_PINS(CONFIG_SECOND_THP_SCL, 4);

  set_SERIAL_PINS(CONFIG_DUST_TX, 1);
  set_SERIAL_PINS(CONFIG_DUST_RX, 2);

  // DUST SENSOR setup - START
#if defined(DUSTSENSOR_PMS5003_7003_BME280_0x76) || defined(DUSTSENSOR_PMS5003_7003_BME280_0x77)
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
    if (LUFTDATEN_ON or THINGSPEAK_ON or INFLUXDB_ON or MQTT_ON) {
      SENDING_FREQUENCY_interval = SENDING_FREQUENCY_interval * SENDING_FREQUENCY;
    }
#ifdef ARDUINO_ARCH_ESP32
#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  int(SENDING_FREQUENCY_interval/1000)        /* Time ESP32 will go to sleep (in seconds) */
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    Serial.println(("Setup ESP32 to sleep for every ") + String(TIME_TO_SLEEP) + (" Seconds\n"));
#endif
  } else {
    if (LUFTDATEN_ON) {
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
    thpSensor.setup();
#endif
  }
  // } else if (!strcmp(THP_MODEL, "BMP280")) {
  //   //Wire.begin(0, 2);
  //   Wire.begin(FIRST_THP_SDA, FIRST_THP_SCL);
  //   bmp.begin();
  // } else if (!strcmp(THP_MODEL, "HTU21")) {
  //   ht2x.begin();
  // } else if (!strcmp(THP_MODEL, "DHT22")) {
  //   dht.begin(FIRST_THP_SDA);
  // } else if (!strcmp(THP_MODEL, "SHT1x")) {
  // } else if (!strcmp(THP_MODEL, "DS18B20")) {
  //   DS18B20.begin();
  // }

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

  Serial.println(("\nIP Address: ") + String(WiFi.localIP().toString()) + ("\n"));
  Serial.print("HTTPServer ready! http://" + String(device_name) + ".local/\n");

  // check update
  unsigned char checkUpdate_x = 0;

  //  ASYNC_WebServer config - Start
  server.on("/", HTTP_GET, handle_root);
  // server.on("/config", HTTP_GET, handle_config);
  // server.on("/config_device_save", HTTP_GET, handle_config_device_save);
  // server.on("/config_device", HTTP_GET, handle_config_device);
  // server.on("/config_services_save", HTTP_GET, handle_config_services_save);
  // server.on("/config_services", HTTP_GET, handle_config_services);
  // server.on("/config_adv_mqtt_save", HTTP_GET, handle_adv_mqtt_config_save);
  // server.on("/config_adv_mqtt", HTTP_GET, handle_adv_mqtt_config);
  // server.on("/update", HTTP_GET, handle_update);
  // server.on("/update_done", HTTP_POST, handle_update_done, handle_update_progress_cb);
  // server.on("/api", HTTP_GET, handle_api);
  // server.on("/erase_wifi", HTTP_GET, erase_wifi);
  // server.on("/restore_config", HTTP_GET, restore_config);
  // server.on("/fwupdate", HTTP_GET, fwupdate);
  // server.on("/autoupdate_on", HTTP_GET, autoupdate_on);
  // server.on("/homekit_reset", HTTP_GET, homekit_reset);
  // server.on("/homekit_on", HTTP_GET, homekit_on);
  // server.on("/homekit_off", HTTP_GET, homekit_off);
  //server.on("/logout", HTTP_GET, logout);
  server.onNotFound(handle_root);


  // Check if defaultConfig.hpp exist in ESP data folder
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

  Serial.print("HTTPServer ready! http://" + String(device_name) + ".local/\n");

#ifdef ASYNC_WEBSERVER_ON
  yield();
#else
  delay(300);
#endif

  if (LUFTDATEN_GRAPH_ON) {
    getAPIIDFromLuftdaten();
  }

}




void updateTHPMeasurements () {
    currentTemperature = thpSensor.getTemperature();
    currentHumidity = thpSensor.getHumidity();
    currentHumidity = thpSensor.getPressure();
}

void sendDataToExternalServices() {

  if (LUFTDATEN_ON) {
    sendDataToLuftdaten(currentTemperature, currentPressure, currentHumidity, averagePM1, averagePM25, averagePM4, averagePM10);
    if (DEBUG) {
      Serial.println(("Sending measurement data to the LuftDaten service!\n"));
    }
  }

}

void loop() {

  yield();

  pm_calibration(thpSensor.getTemperature(), thpSensor.getHumidity());

  // DUST SENSOR refresh data - START
#if defined(DUSTSENSOR_PMS5003_7003_BME280_0x76) || defined(DUSTSENSOR_PMS5003_7003_BME280_0x77)
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

      if (LUFTDATEN_ON) {
        
        updateTHPMeasurements();
        sendDataToExternalServices();
      }
      if (THINGSPEAK_ON or INFLUXDB_ON or MQTT_ON) {
        updateTHPMeasurements();
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
      if (LUFTDATEN_ON) {
        updateTHPMeasurements();
        sendDataToExternalServices();
      }
      if (THINGSPEAK_ON or INFLUXDB_ON or MQTT_ON) {
        updateTHPMeasurements();
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

  if (LUFTDATEN_ON) {
    unsigned int current_SENDING_FREQUENCY_Millis = millis();
    if (current_SENDING_FREQUENCY_Millis - previous_SENDING_FREQUENCY_Millis >= SENDING_FREQUENCY_interval) {
        updateTHPMeasurements();
      sendDataToExternalServices();
      previous_SENDING_FREQUENCY_Millis = millis();
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

