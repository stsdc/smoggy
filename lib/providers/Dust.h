#ifndef DUST_H
#define DUST_H

#include <Arduino.h>

#include "config.h"
#include "../include/defaultConfig.h"

#ifdef ASYNC_WEBSERVER_ON
#include "../lib/smogly_asyncwebserver.h"
#else
#include "../lib/smogly_webserver.h"
#endif



#define DUSTSENSOR_PMS5003_7003_BME280_0x76 // PMS5003 / PMS7003 - BME280_0x76
// #define DUSTSENSOR_PMS5003_7003_BME280_0x77 // PMS5003 / PM§S7003 - BME280_0x77
// #define DUSTSENSOR_SDS011_21 // Nova Fitness SDS011 / SDS021
// #define DUSTSENSOR_HPMA115S0 // Honeywell HPMA115S0
// #define DUSTSENSOR_SPS30 // Sensirion SPS30

#ifdef DUSTSENSOR_PMS5003_7003_BME280_0x76 or DUSTSENSOR_PMS5003_7003_BME280_0x77
#include "PMS.h" // https://github.com/fu-hsi/PMS // 5.11.2021
#elif defined DUSTSENSOR_SDS011_21
#ifdef ARDUINO_ARCH_ESP8266
#include "src/libs/esp8266/SdsDustSensor.h" // SDS011/SDS021 - https://github.com/lewapek/sds-dust-sensors-arduino-library // 5.11.2021
#elif defined ARDUINO_ARCH_ESP32
// #include "src/libs/esp8266/SdsDustSensor.h" // SDS011/SDS021 - https://github.com/lewapek/sds-dust-sensors-arduino-library // 5.11.2021
#include "src/libs/esp32/SDS011.h" // https://github.com/ricki-z/SDS011 // 5.11.2021
#endif
#elif defined DUSTSENSOR_HPMA115S0
#include "src/libs/hpma115S0.h" // https://github.com/hpsaturn/HPMA115S0 // 5.11.2021
#elif defined DUSTSENSOR_SPS30
#include "src/libs/sps30.h" // https://github.com/paulvha/sps30 // CUSTOMIZED! 5.11.2021
#else // If no dust sensor has been defined - use DUSTSENSOR_PMS5003_7003_BME280_0x76
#include "src/libs/pms.h" // https://github.com/fu-hsi/PMS // 5.11.2021
#endif

// DUST Sensor config - START

#ifdef DUSTSENSOR_PMS5003_7003_BME280_0x76 or DUSTSENSOR_PMS5003_7003_BME280_0x77
//***PMSx003 - START***
#ifdef ARDUINO_ARCH_ESP8266
#ifdef ARDUINO_ESP8266_RELEASE_2_6_0
SoftwareSerial PMS_Serial; // only for esp8266 core 2.6.0
#else
SoftwareSerial PMS_Serial(DUST_TX, DUST_RX); // Change TX - D1 and RX - D2 pins -- esp8266 core 2.6.1 or later
#endif
PMS pms(PMS_Serial);
PMS::DATA data;
#elif defined ARDUINO_ARCH_ESP32
HardwareSerial PMS_Serial(1); // Change TX - D5 and RX - D4 pins
PMS pms(PMS_Serial);
PMS::DATA data;
#endif
//***PMSx003 - END***
#elif defined DUSTSENSOR_SDS011_21
//***SDS0x1 - START***
#ifdef ARDUINO_ARCH_ESP8266
// SDS011/21 config
SdsDustSensor sds(DUST_TX, DUST_RX); // Change TX - D1 and RX - D2 pins
#elif defined ARDUINO_ARCH_ESP32
// SDS011/21 config
HardwareSerial sds_port(2); // Change TX - D5 and RX - D4 pins
SDS011 my_sds;
int err;
float SDSpm25, SDSpm10;
#endif
//***SDS0x1 - END***
#elif defined DUSTSENSOR_HPMA115S0
//***HPMA115S0 - START***
#ifdef ARDUINO_ARCH_ESP8266
SoftwareSerial hpmaSerial(DUST_TX, DUST_RX); // TX/RX – D1/D2
HPMA115S0 hpma115S0(hpmaSerial);
#elif defined ARDUINO_ARCH_ESP32
HardwareSerial hpmaSerial(1); // Change TX - D5 and RX - D4 pins
HPMA115S0 hpma115S0(hpmaSerial);
#endif
unsigned int hpma115S0_pm25, hpma115S0_pm10;
//***HPMA115S0 - END***
#elif defined DUSTSENSOR_SPS30
//***SPS30 - START***
#ifdef ARDUINO_ARCH_ESP8266
#define SP30_COMMS I2C_COMMS
#elif defined ARDUINO_ARCH_ESP32
#define SP30_COMMS SERIALPORT1
#endif
#define SPS30_AUTOCLEANINTERVAL -1
#define SPS30_PERFORMCLEANNOW 1
#define SPS30_DEBUG 0
// function prototypes (sometimes the pre-processor does not create prototypes themself on ESPxx)
void ErrtoMess(char *mess, uint8_t r);
void Errorloop(char *mess, uint8_t r);
void GetDeviceInfo();
bool read_sps30_data();
// create constructor
SPS30 sps30;
float SPS30_PM1, SPS30_PM25, SPS30_PM4, SPS30_PM10;
//***SPS30 - END***
#else // If no dust sensor has been defined - use DUSTSENSOR_PMS5003_7003_BME280_0x76
//***PMSx003 - START***
#ifdef ARDUINO_ARCH_ESP8266
#ifdef ARDUINO_ESP8266_RELEASE_2_6_0
SoftwareSerial PMS_Serial; // only for esp8266 core 2.6.0
#else
SoftwareSerial PMS_Serial(DUST_TX, DUST_RX); // Change TX - D1 and RX - D2 pins -- esp8266 core 2.6.1 or later
#endif
PMS pms(PMS_Serial);
PMS::DATA data;
#elif defined ARDUINO_ARCH_ESP32
HardwareSerial PMS_Serial(1); // Change TX - D5 and RX - D4 pins
PMS pms(PMS_Serial);
PMS::DATA data;
#endif
//***PMSx003 - END***
#endif

// DUST Sensor config - END


#ifdef DUSTSENSOR_SPS30
static unsigned short pmMeasurements[10][4];
#else
static unsigned short pmMeasurements[10][3];
#endif

static unsigned short averagePM1, averagePM25, averagePM4, averagePM10 = 0;
static unsigned char iPM = 0;
unsigned int previous_2sec_Millis = 0;
static unsigned short TwoSec_interval = 2 * 1000; // 2 second

void pm_calibration();
void takeNormalnPMMeasurements();
void takeSleepPMMeasurements();

#endif
