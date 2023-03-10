#include <Webpage.hpp>
#include <TemperatureHumidityPressureSensor.hpp>
#include <DustSensor.h>

#include <Luftdaten.hpp>
#include <Aqieco.hpp>
#include <SmoggyFirebase.hpp>
#include <SmoggyDeepSleep.hpp>
#include <smogly_spiffs.hpp>
#include <SmoggyBattery.hpp>
#include <LittleFS.h>

// Pins for temperature, humidity, pressure sensor
unsigned int PIN_SDA_THP = 21;
unsigned int PIN_SCL_THP = 22;

// Pins for dust sensor
int PIN_RX_DUST = 16;
int PIN_TX_DUST = 17;

TemperatureHumidityPressureSensor thpSensor = TemperatureHumidityPressureSensor(PIN_SDA_THP, PIN_SCL_THP);
DustSensor dustSensor                       = DustSensor(PIN_RX_DUST, PIN_TX_DUST);
Battery    battery;

SmoggyFirebase  smoggyFirebase;
SmoggyPortal    smoggyPortal;
SmoggyDeepSleep smoggyDeepSleep;

Luftdaten luftdaten;
Aqieco    aqieco;

String get_mac_as_id() {
  String macAddress = WiFi.macAddress();

  macAddress.replace(":", "");
  macAddress.toLowerCase();
  return macAddress;
}

// RAM:   [=         ]  14.7% (used 48012 bytes from 327680 bytes)
// Flash: [======    ]  64.7% (used 1271345 bytes from 1966080 bytes)


String smoggy_get_id() {
#if defined(ESP8266)
  return String(ESP.getChipId());

#elif defined(ESP32)
  return String((uint32_t)(ESP.getEfuseMac()));

#endif // if defined(ESP8266)
}




void setup() {
  Serial.begin(115200);

  delay(1000);

  fs_setup();

  smoggyDeepSleep.setup(MEASURMENT_INTERVAL);

  thpSensor.setup();
  dustSensor.setup(DUST_NUMBEROFMEASUREMENTS);

  Serial.println("X-Sensor: smogomierz-" + smoggy_get_id());
  smoggyPortal.setup();


  // smoggyFirebase.setup();
  // smoggyFirebase.send();
}

void measure_and_send() {
  dustSensor.calibrate(thpSensor.getTemperature(), thpSensor.getHumidity());

  dustSensor.takeSleepPMMeasurements();

  auto dust                 = dustSensor.get_average();
  auto temperature          = thpSensor.getTemperature();
  auto humidity             = thpSensor.getHumidity();
  auto pressure             = thpSensor.getPressure();
  unsigned short DEFAULT_PM = 0;
  luftdaten.send(dust.PM1, dust.PM2_5, dust.PM10, temperature, pressure, humidity);
  aqieco.send(dust.PM1, dust.PM2_5, dust.PM10, temperature, pressure, humidity, battery);
}

void loop() {
  smoggyPortal.portal.handleClient();

  if (smoggyDeepSleep.DEEP_SLEEP_EN) {
    battery.sample(BAT_NUMBEROFMEASUREMENTS, BAT_DELAY);
    battery.print();

    // preventing to run power expensive measurements if battery close to discharge
    // also battery might be not connected, neglecting empty measurements
    if ((battery.vbat >= 3.31) || (battery.get_percentage() < 0)) {
      measure_and_send();
    } else {
      Serial.println("⚠️ Battery low. No measuring for now...");
    }

    Serial.println("💤 Going to sleep now...");
    Serial.flush();

    smoggyDeepSleep.start();
  }
}
