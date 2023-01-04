#include "SmoggyDeepSleep.hpp"

SmoggyDeepSleep::SmoggyDeepSleep() {}

void SmoggyDeepSleep::setup(int measurement_interval) {
  this->DEEP_SLEEP_EN = true;
  this->MEASURMENT_INTERVAL = measurement_interval;

#if defined(ESP8266)
#elif defined(ESP32)

  // DeepSleep is enabled by default.
  // Pressing BOOT button will wakeup the device and disable sleep.
  esp_sleep_enable_timer_wakeup(measurement_interval / 1000 * uS_TO_S_FACTOR);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_0, 0);

  esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();

  if (wakeup_reason == ESP_SLEEP_WAKEUP_EXT0) {
    DEEP_SLEEP_EN = false;
    Serial.println("💤 DeepSleep disabled.");
  } else {
    Serial.println("💤 DeepSleep for " + String(measurement_interval / 1000) + " seconds enabled.");
  }
  #endif
}

void SmoggyDeepSleep::start() {

#if defined(ESP8266)
 ESP.deepSleep(this->MEASURMENT_INTERVAL / 1000 * uS_TO_S_FACTOR);
#elif defined(ESP32)
      esp_deep_sleep_start();
#endif

}