#include <Arduino.h>

#include "TemperatureHumidityPressureSensor.hpp"

TemperatureHumidityPressureSensor::TemperatureHumidityPressureSensor(unsigned char PIN_SDA, unsigned char PIN_SCL) : bme((uint8_t)PIN_SDA, (uint8_t)PIN_SCL){
}


void TemperatureHumidityPressureSensor::setup() {
    // Adafruit_BME280 bme((uint8_t)PIN_SDA, (uint8_t)PIN_SCL);

    if (!bme.begin()) {
      Serial.println("\nCould not find a valid BME280 sensor, check wiring!\n");
    }
}

float TemperatureHumidityPressureSensor::getTemperature() {
  Serial.println("🌡️ Temp: " + String(bme.readTemperature()) + "℃");
    return bme.readTemperature();
}

float TemperatureHumidityPressureSensor::getHumidity() {
    return bme.readHumidity();
}

float TemperatureHumidityPressureSensor::getPressure() {
    return bme.seaLevelForAltitude(1.0, (bme.readPressure() / 100.0F));
}

bool TemperatureHumidityPressureSensor::getStatus() {
if ((int)this->getTemperature() == 0 && (int)this->getHumidity() == 0 && (int)this->getPressure() == 0) {
    if (true) {
      Serial.println(("No data from BME280 sensor!\n"));
    }
    return false;
  }
  return true;
}

// bool checkBmeStatus() {
// #ifdef ARDUINO_ARCH_ESP8266
//   int temperature_BME280_Int = BMESensor.temperature;
//   int pressure_BME280_Int = (BMESensor.seaLevelForAltitude(MYALTITUDE));
//   int humidity_BME280_Int = BMESensor.humidity;
// #elif defined ARDUINO_ARCH_ESP32
//   int temperature_BME280_Int = bme.readTemperature();
//   int pressure_BME280_Int = (bme.seaLevelForAltitude(MYALTITUDE, (bme.readPressure() / 100.0F)));
//   int humidity_BME280_Int = bme.readHumidity();
// #endif
//   if (temperature_BME280_Int == 0 && pressure_BME280_Int == 0 && humidity_BME280_Int == 0) {
//     if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//       Serial.println(F("No data from BME280 sensor!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//       Serial.println(("No data from BME280 sensor!\n"));
// #endif
//     }
//     return false;
//   } else {
//     return true;
//   }
// }

// check TEMP/HUMI/PRESS Sensor - START
// bool checkHTU21DStatus() {
//   int temperature_HTU21D_Int = int(ht2x.readTemperature());
//   int humidity_HTU21D_Int = int(ht2x.readHumidity());
//   if ((temperature_HTU21D_Int == 0 && humidity_HTU21D_Int == 0) || (temperature_HTU21D_Int == 255 && humidity_HTU21D_Int == 255)) {
//     if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//       Serial.println(F("No data from HTU21D sensor!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//       Serial.println(("No data from HTU21D sensor!\n"));
// #endif
//     }
//     return false;
//   } else {
//     return true;
//   }
// }

// bool checkBmpStatus() {
//   int temperature_BMP_Int = bmp.readTemperature();
//   int pressure_BMP_Int = bmp.readPressure();
//   if (temperature_BMP_Int == 0 && pressure_BMP_Int == 0) {
//     if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//       Serial.println(F("No data from BMP280 sensor!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//       Serial.println(("No data from BMP280 sensor!\n"));
// #endif
//     }
//     return false;
//   } else {
//     return true;
//   }
// }

// bool checkDHT22Status() {
//   int humidity_DHT_Int = dht.readHumidity();
//   int temperature_DHT_Int = dht.readTemperature();
//   if (humidity_DHT_Int == 0 && temperature_DHT_Int == 0) {
//     if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//       Serial.println(F("No data from DHT22 sensor!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//       Serial.println(("No data from DHT22 sensor!\n"));
// #endif
//     }
//     return false;
//   } else if (isnan(humidity_DHT_Int) && isnan(temperature_DHT_Int)) {
//     if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//       Serial.println(F("No data from DHT22 sensor!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//       Serial.println(("No data from DHT22 sensor!\n"));
// #endif
//     }
//     return false;
//   } else {
//     return true;
//   }
// }

// bool checkSHT1xStatus() {
//   int humidity_SHT1x_Int = sht1x.readHumidity();
//   int temperature_SHT1x_Int = sht1x.readTemperatureC();
//   if (humidity_SHT1x_Int == 0 && temperature_SHT1x_Int == 0) {
//     if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//       Serial.println(F("No data from SHT1x sensor!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//       Serial.println(("No data from SHT1x sensor!\n"));
// #endif
//     }
//     return false;
//   } else {
//     return true;
//   }
// }

// bool checkDS18B20Status() {
//   /*
//     DS18B20.requestTemperatures();
//     int temperature_DS18B20_Int = DS18B20.getTempCByIndex(0);
//     if (temperature_DS18B20_Int == -127) {
//     if (DEBUG) {
//     #ifdef ARDUINO_ARCH_ESP8266
//       Serial.println(F("No data from DS18B20 sensor!\n"));
//     #elif defined ARDUINO_ARCH_ESP32
//       Serial.println(("No data from DS18B20 sensor!\n"));
//     #endif
//     }
//     return false;
//     } else {
//     return true;
//     }
//   */
//   return true;
// }


// TempHumiPres takeTHPMeasurements() {
//   float currentTemperature_THP1, currentHumidity_THP1, currentPressure_THP1 = 0;
//   float currentTemperature_THP2, currentHumidity_THP2, currentPressure_THP2 = 0;

//   if (!strcmp(THP_MODEL, "BME280")) {

// #ifdef ARDUINO_ARCH_ESP8266
//     BMESensor.refresh(FIRST_THP_SDA, FIRST_THP_SCL);
// #endif
//     if (checkBmeStatus() == true) {
//       if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//         Serial.println(F("Measurements from BME280!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//         Serial.println(("Measurements from BME280!\n"));
// #endif
//       }
// #ifdef ARDUINO_ARCH_ESP8266
//       currentTemperature_THP1 = BMESensor.temperature;
//       currentPressure_THP1 = BMESensor.seaLevelForAltitude(MYALTITUDE);
//       currentHumidity_THP1 = BMESensor.humidity;
// #elif defined ARDUINO_ARCH_ESP32
//     //   currentTemperature_THP1 = (bme.readTemperature()); // maybe *0.89 ?
//     //   currentPressure_THP1 = (bme.seaLevelForAltitude(MYALTITUDE, (bme.readPressure() / 100.0F)));
//     //   currentHumidity_THP1 = (bme.readHumidity()); // maybe *0.89 ?
// #endif

//     } else {
//       if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//         Serial.println(F("No measurements from BME280!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//         Serial.println(("No measurements from BME280!\n"));
// #endif
//       }
//     }
//   } else if (!strcmp(THP_MODEL, "HTU21")) {
//     if (checkHTU21DStatus() == true) {
//       if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//         Serial.println(F("Measurements from HTU21!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//         Serial.println(("Measurements from HTU21!\n"));
// #endif
//       }
//       currentTemperature_THP1 = ht2x.readTemperature();
//       currentHumidity_THP1 = ht2x.readHumidity();
//     } else {
//       if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//         Serial.println(F("No measurements from HTU21D!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//         Serial.println(("No measurements from HTU21D!\n"));
// #endif
//       }
//     }
//   } else if (!strcmp(THP_MODEL, "BMP280")) {
//     if (checkBmpStatus() == true) {
//       if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//         Serial.println(F("Measurements from BMP280!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//         Serial.println(("Measurements from BMP280!\n"));
// #endif
//       }
//       currentTemperature_THP1 = bmp.readTemperature();
//       currentPressure_THP1 = (bmp.readPressure()) / 100;
//     } else {
//       if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//         Serial.println(F("No measurements from BMP280!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//         Serial.println(("No measurements from BMP280!\n"));
// #endif
//       }
//     }
//   } else if (!strcmp(THP_MODEL, "DHT22")) {
//     if (checkDHT22Status() == true) {
//       if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//         Serial.println(F("Measurements from DHT22!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//         Serial.println(("Measurements from DHT22!\n"));
// #endif
//       }
//       currentTemperature_THP1 = dht.readTemperature();
//       currentHumidity_THP1 = dht.readHumidity();
//     } else {
//       if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//         Serial.println(F("No measurements from DHT22!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//         Serial.println(("No measurements from DHT22!\n"));
// #endif
//       }
//     }
//   } else if (!strcmp(THP_MODEL, "SHT1x")) {
//     if (checkSHT1xStatus() == true) {
//       if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//         Serial.println(F("Measurements from SHT1x!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//         Serial.println(("Measurements from SHT1x!\n"));
// #endif
//       }
//       currentTemperature_THP1 = sht1x.readTemperatureC();
//       currentHumidity_THP1 = sht1x.readHumidity();
//     } else {
//       if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//         Serial.println(F("No measurements from SHT1x!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//         Serial.println(("No measurements from SHT1x!\n"));
// #endif
//       }
//     }
//   } else if (!strcmp(THP_MODEL, "DS18B20")) {
//     if (checkDS18B20Status() == true) {
//       if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//         Serial.println(F("Measurements from DS18B20!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//         Serial.println(("Measurements from DS18B20!\n"));
// #endif
//       }
//       DS18B20.requestTemperatures();
//       currentTemperature_THP1 = DS18B20.getTempCByIndex(0);
//     } else {
//       if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//         Serial.println(F("No measurements from DS18B20!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//         Serial.println(("No measurements from DS18B20!\n"));
// #endif
//       }
//     }
//   }

//   if (SECOND_THP) {
//     if (!strcmp(SECOND_THP_MODEL, "BME280")) {
// #ifdef ARDUINO_ARCH_ESP8266
//       BMESensor_2.refresh(SECOND_THP_SDA, SECOND_THP_SCL);
// #endif
//       if (checkBmeStatus() == true) {
//         if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//           Serial.println(F("Measurements from BME280!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//           Serial.println(("Measurements from BME280!\n"));
// #endif
//         }
// #ifdef ARDUINO_ARCH_ESP8266
//         currentTemperature_THP2 = BMESensor_2.temperature;
//         currentPressure_THP2 = BMESensor_2.seaLevelForAltitude(MYALTITUDE);
//         currentHumidity_THP2 = BMESensor_2.humidity;
// #elif defined ARDUINO_ARCH_ESP32
//         // currentTemperature_THP2 = (bme.readTemperature()); // maybe *0.89 ?
//         // currentPressure_THP2 = (bme.seaLevelForAltitude(MYALTITUDE, (bme.readPressure() / 100.0F)));
//         // currentHumidity_THP2 = (bme.readHumidity()); // maybe *0.89 ?
// #endif
//       } else {
//         if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//           Serial.println(F("No measurements from BME280!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//           Serial.println(("No measurements from BME280!\n"));
// #endif
//         }
//       }
//     } else if (!strcmp(SECOND_THP_MODEL, "HTU21")) {
//       if (checkHTU21DStatus() == true) {
//         if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//           Serial.println(F("Measurements from HTU21!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//           Serial.println(("Measurements from HTU21!\n"));
// #endif
//         }
//         currentTemperature_THP2 = ht2x.readTemperature();
//         currentHumidity_THP2 = ht2x.readHumidity();
//       } else {
//         if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//           Serial.println(F("No measurements from HTU21D!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//           Serial.println(("No measurements from HTU21D!\n"));
// #endif
//         }
//       }
//     } else if (!strcmp(SECOND_THP_MODEL, "BMP280")) {
//       if (checkBmpStatus() == true) {
//         if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//           Serial.println(F("Measurements from BMP280!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//           Serial.println(("Measurements from BMP280!\n"));
// #endif
//         }
//         currentTemperature_THP2 = bmp.readTemperature();
//         currentPressure_THP2 = (bmp.readPressure()) / 100;
//       } else {
//         if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//           Serial.println(F("No measurements from BMP280!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//           Serial.println(("No measurements from BMP280!\n"));
// #endif
//         }
//       }
//     } else if (!strcmp(SECOND_THP_MODEL, "DHT22")) {
//       if (checkDHT22Status() == true) {
//         if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//           Serial.println(F("Measurements from DHT22!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//           Serial.println(("Measurements from DHT22!\n"));
// #endif
//         }
//         currentTemperature_THP2 = dht.readTemperature();
//         currentHumidity_THP2 = dht.readHumidity();
//       } else {
//         if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//           Serial.println(F("No measurements from DHT22!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//           Serial.println(("No measurements from DHT22!\n"));
// #endif
//         }
//       }
//     } else if (!strcmp(SECOND_THP_MODEL, "SHT1x")) {
//       if (checkSHT1xStatus() == true) {
//         if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//           Serial.println(F("Measurements from SHT1x!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//           Serial.println(("Measurements from SHT1x!\n"));
// #endif
//         }
//         currentTemperature_THP2 = sht1x.readTemperatureC();
//         currentHumidity_THP2 = sht1x.readHumidity();
//       } else {
//         if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//           Serial.println(F("No measurements from SHT1x!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//           Serial.println(("No measurements from SHT1x!\n"));
// #endif
//         }
//       }
//     } else if (!strcmp(SECOND_THP_MODEL, "DS18B20")) {
//       if (checkDS18B20Status() == true) {
//         if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//           Serial.println(F("Measurements from DS18B20!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//           Serial.println(("Measurements from DS18B20!\n"));
// #endif
//         }
//         DS18B20.requestTemperatures();
//         currentTemperature_THP2 = DS18B20.getTempCByIndex(0);
//       } else {
//         if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//           Serial.println(F("No measurements from DS18B20!\n"));
// #elif defined ARDUINO_ARCH_ESP32
//           Serial.println(("No measurements from DS18B20!\n"));
// #endif
//         }
//       }
//     }
//   }

//   //temporary solution!
// //   currentTemperature = currentTemperature_THP1;
// //   currentHumidity = currentHumidity_THP1;
// //   currentPressure = currentPressure_THP1;

// #ifdef ARDUINO_ARCH_ESP32
//   if (HOMEKIT_SUPPORT) {
//     // homekit_DeviceData.homekit_temperature = currentTemperature;
//     // homekit_DeviceData.homekit_humidity = currentHumidity;
//     // notify_hap();
//   }
// #endif
//   return {
//     currentTemperature_THP1,
//     currentHumidity_THP1,
//     currentPressure_THP1
//   };
// }
