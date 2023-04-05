#include <Arduino.h>

#include "TemperatureHumidityPressureSensor.hpp"

TemperatureHumidityPressureSensor::TemperatureHumidityPressureSensor(unsigned char PIN_SDA,
                                                                     unsigned char PIN_SCL) : bme((uint8_t)PIN_SDA,
                                                                                                  (uint8_t)PIN_SCL) {}

void TemperatureHumidityPressureSensor::setup() {
  // Adafruit_BME280 bme((uint8_t)PIN_SDA, (uint8_t)PIN_SCL);

  Serial.print("🌡️  Setup BME280 sensor at 0x");
  Serial.print(SMOGGY_I2C_THP_ADDR, HEX);
  Serial.println();

  if (!bme.begin(SMOGGY_I2C_THP_ADDR)) {
    Serial.println("\nCould not find a valid BME280 sensor, check wiring!\n");
  }
}

float TemperatureHumidityPressureSensor::getTemperature() {
  return bme.readTemperature();
}

float TemperatureHumidityPressureSensor::getHumidity() {
  return bme.readHumidity();
}

float TemperatureHumidityPressureSensor::getPressure() {
  return bme.seaLevelForAltitude(1.0, (bme.readPressure() / 100.0F));
}

bool TemperatureHumidityPressureSensor::getStatus() {
  Serial.println("🌡️  Temp: " + String(bme.readTemperature()) + "℃");

  if (((int)this->getTemperature() == 0) && ((int)this->getHumidity() == 0) && ((int)this->getPressure() == 0)) {
    if (true) {
      Serial.println(("No data from BME280 sensor!\n"));
    }
    return false;
  }
  return true;
}
