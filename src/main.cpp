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

TemperatureHumidityPressureSensor thpSensor = TemperatureHumidityPressureSensor(21, 22);
DustSensor dustSensor                       = DustSensor();
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
#endif
}

unsigned char DUST_TIME            = 1;
unsigned char NUMBEROFMEASUREMENTS = 10;

unsigned int MEASURMENT_INTERVAL = 120e3; // in ms


void setup() {
  Serial.begin(115200);

  delay(1000);

  fs_setup();

  smoggyDeepSleep.setup(MEASURMENT_INTERVAL);

  thpSensor.setup();
  dustSensor.setup(10);

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
    battery.get_percentage();
    measure_and_send();
    Serial.println("💤 Going to sleep now...");
    Serial.flush();

    smoggyDeepSleep.start();
  }
  battery.get_percentage();
}
