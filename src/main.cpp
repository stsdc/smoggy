#include <WiFi.h>      // Replace with WiFi.h for ESP32
#include <WebServer.h> // Replace with WebServer.h for ESP32
#include <Webpage.hpp>



#include <TemperatureHumidityPressureSensor.hpp>
#include <DustSensor.h>

#include <Luftdaten.hpp>
#include <Aqieco.hpp>
#include <SmoggyFirebase.hpp>

#include <smogly_spiffs.hpp>
#include <SmoggyBattery.hpp>
#include <LittleFS.h>

TemperatureHumidityPressureSensor thpSensor = TemperatureHumidityPressureSensor(21, 22);
DustSensor dustSensor = DustSensor();
Battery battery;

SmoggyFirebase smoggyFirebase;
SmoggyPortal smoggyPortal;

Luftdaten luftdaten;
Aqieco aqieco;

String get_mac_as_id() {
  String macAddress = WiFi.macAddress();

  macAddress.replace(":", "");
  macAddress.toLowerCase();
  return macAddress;
}

bool DEEP_SLEEP_EN = true;

unsigned char DUST_TIME            = 1;
unsigned char NUMBEROFMEASUREMENTS = 10;

unsigned int MEASURMENT_INTERVAL = 120e3; // in ms

#define uS_TO_S_FACTOR 1000000ULL         /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP_uS MEASURMENT_INTERVAL / 1000 * uS_TO_S_FACTOR

void setup() {
  Serial.begin(115200);
  delay(1000);

  fs_setup();
  // DeepSleep is enabled by default.
  // Pressing BOOT button will wakeup the device and disable sleep.
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP_uS);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_0, 0);

  esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
  if (wakeup_reason == ESP_SLEEP_WAKEUP_EXT0) {
    DEEP_SLEEP_EN = false;
    Serial.println("💤 DeepSleep disabled.");
  } else {
      Serial.println("💤 DeepSleep for " + String(MEASURMENT_INTERVAL / 1000) + " seconds enabled.");
  }

  thpSensor.setup();
  dustSensor.setup(10);

  Serial.println("X-Sensor: smogomierz-" + String((uint32_t)(ESP.getEfuseMac())));
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

  if (DEEP_SLEEP_EN) {
    battery.get_percentage();
    measure_and_send();
    Serial.println("💤 Going to sleep now...");
    Serial.flush();

    esp_deep_sleep_start();
  }
  battery.get_percentage();

}
