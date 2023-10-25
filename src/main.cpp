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

RTC_DATA_ATTR int boot_counter = 0;


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
  // Stolen from @alicjamusial/meteo-station-code
  setCpuFrequencyMhz(80); // low, 'cause we want long lifetime :)
  delay(1000); // just another one ugly hack

  Serial.begin(115200);

  Serial.println("❤️  Smoggy v" + String(SW_VERSION));

  ++boot_counter;
  Serial.println("⬆️  Boot #" + String(boot_counter));

  if (boot_counter > 10) {
    Serial.println("♻️ Restart...");
    ESP.restart();
  }

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
  if (thpSensor.getStatus()) {
    auto temperature = thpSensor.getTemperature();
    auto humidity    = thpSensor.getHumidity();

    if (isnan(temperature)) {
      Serial.println("⚠️ Temperature sensor returns NaN.");
      Serial.println("♻️ Restart...");
      ESP.restart();
    }

    dustSensor.calibrate(temperature, humidity);

    auto dust                 = dustSensor.getDust();
    auto pressure             = thpSensor.getPressure();
    unsigned short DEFAULT_PM = 0;
    luftdaten.send(dust.PM1, dust.PM2_5, dust.PM10, temperature, pressure, humidity);
    aqieco.send(dust.PM1, dust.PM2_5, dust.PM10, temperature, pressure, humidity, battery);
  }
}

void loop() {
  smoggyPortal.portal.handleClient();

  if (smoggyDeepSleep.DEEP_SLEEP_EN) {
    battery.sampling_on(BAT_NUMBEROFMEASUREMENTS, BAT_DELAY);
    battery.print();

    // preventing to run power expensive measurements if battery close to
    // discharge;
    // also battery might be not connected, neglecting empty measurements

    if (battery.vbat <= 3.50) {
      smoggyDeepSleep.setup(MEASURMENT_INTERVAL_LOW_BATTERY);
      Serial.println("⚠️ Battery low. Measurment interval increased...");
    }

    if ((battery.vbat >= 3.31)) {
      measure_and_send();
    } else {
      Serial.println("⚠️ Battery very low. No measuring for now...");
    }

    Serial.println("💤 Going to sleep now...");
    Serial.flush();
    battery.sampling_off();
    smoggyDeepSleep.start();
  }
}
