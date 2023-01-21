// #ifndef TEMP_HUMI_PRES_H
// #define TEMP_HUMI_PRES_H


#include <Adafruit_BME280.h>

// #include "../../src/defaultConfig.h"

// #ifdef ARDUINO_ARCH_ESP8266
// #ifndef DUSTSENSOR_PMS5003_7003_BME280_0x77
// #include "src/libs/esp8266/bme280_0x76.h" // https://github.com/zen/BME280_light // CUSTOMIZED! 5.11.2021
// #else
// #include "src/libs/esp8266/bme280_0x77.h" // https://github.com/zen/BME280_light // CUSTOMIZED! 5.11.2021
// #endif
// #elif defined ARDUINO_ARCH_ESP32
// #include <Adafruit_BME280.h> // https://github.com/Takatsuki0204/BME280-I2C-ESP32 // 5.11.2021
// #endif

// #include <HTU2xD_SHT2x_Si70xx.h> // https://github.com/enjoyneering/HTU2xD_SHT2x_Si70xx // 5.11.2021
// #include <Adafruit_BMP280.h> // https://github.com/adafruit/Adafruit_BMP280_Library // 5.11.2021
// #include <SHT1x.h> // https://github.com/practicalarduino/SHT1x // 5.11.2021
// #include <DHT.h> // https://github.com/adafruit/DHT-sensor-library // 5.11.2021

// #include <OneWire.h>
// #include <DallasTemperature.h>

// DS18B20 – Config
//const int DS18B20_WireBus = 14; // D5
//OneWire oneWire(FIRST_THP_SDA);
// OneWire oneWire(14);
// DallasTemperature DS18B20(&oneWire);
// TEMP/HUMI/PRESS Sensor config - END


// TEMP/HUMI/PRESS Sensor config - START
// BME280 config
// #ifdef ARDUINO_ARCH_ESP8266 // VIN - 3V; GND - G; SCL - D4; SDA - D3
// #define ASCII_ESC 27
// char bufout[10];
// BME280<> BMESensor;
// BME280<> BMESensor_2;
// #elif defined ARDUINO_ARCH_ESP32 // VIN - 3V; GND - G; SCL - D17; SDA - D16
// //#define I2C_SDA = FIRST_THP_SDA
// //#define I2C_SCL = FIRST_THP_SCL
// // Adafruit_BME280 bme((uint8_t)FIRST_THP_SDA, (uint8_t)FIRST_THP_SCL); // I2C -- ONLY THE DEFAULT VALUES WORK
// #endif

// // Serial for SHT21/HTU21D config
// // HTU21D  myHTU21D(HTU21D_RES_RH12_TEMP14);
// HTU2xD_SHT2x_SI70xx ht2x(HTU2xD_SENSOR, HUMD_12BIT_TEMP_14BIT); //sensor type, resolution

// // BMP280 config
// Adafruit_BMP280 bmp; //I2C

// // DHT22 config
// //#define DHTPIN 13 // D7 on NodeMCU/WeMos board
// #define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
// DHT dht(FIRST_THP_SDA, DHTTYPE);

// // SHT1x – Config
// //#define dataPin 14 //D5
// //#define clockPin 12 //D6
// SHT1x sht1x(FIRST_THP_SDA, FIRST_THP_SCL);


// struct TempHumiPres {
//     float temperature;
//     float humidity;
//     float pressure;
// };

// bool checkHTU21DStatus();
// bool checkBmpStatus();
// bool checkBmeStatus();
// bool checkDHT22Status();
// bool checkSHT1xStatus();
// bool checkDS18B20Status();

// TempHumiPres takeTHPMeasurements();

class TemperatureHumidityPressureSensor {
    private:
        Adafruit_BME280 bme; // I2C -- ONLY THE DEFAULT VALUES WORK

    public:
        float getTemperature();
        float getHumidity();
        float getPressure();
        bool getStatus();
        void setup();
        TemperatureHumidityPressureSensor(unsigned char, unsigned char);
};

// #endif