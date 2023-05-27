#include "SmoggyBattery.hpp"

Battery::Battery() {
  esp_adc_cal_characteristics_t VoltageCharacteristics;
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten((adc1_channel_t)ADC_CHANNEL_6, ADC_ATTEN_DB_11);
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &VoltageCharacteristics);
}

void Battery::sampling_on(int num_of_samples, int delay_between_samples) {
  int adc_sum = 0;

  for (int i = 0; i < num_of_samples; i++) {
    adc_sum += analogRead(PIN_ADC_BAT);
    delay(delay_between_samples);
  }

  this->vin  = ((adc_sum / num_of_samples) * ADC_REFERENCE) / (4095);
  this->vbat = ((R1 + R2) * this->vin) / R2;
}

void Battery::sampling_off() {
  adc_power_off();
}

float Battery::get_percentage() {
  return 100 * (this->vbat - VOLTAGE_BAT_MIN) / (VOLTAGE_BAT_MAX - VOLTAGE_BAT_MIN);
}

void Battery::print() {
  Serial.println(
    "⚡ Battery: Vin: " + String(this->vin) +
    " Vbat: " + String(this->vbat) +
    " Usage: " + String(this->get_percentage()) + "%");
}
