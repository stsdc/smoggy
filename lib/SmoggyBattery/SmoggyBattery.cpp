#include "SmoggyBattery.hpp"

Battery::Battery() {}

float Battery::get_vin() {
  return (analogRead(PIN_ADC_BAT) * ADC_REFERENCE) / (4095);
}

float Battery::get_vbat() {
  return ((R1 + R2) * this->get_vin()) / R2;
}

float Battery::get_percentage() {
  return 100 * (this->get_vbat() - VOLTAGE_BAT_MIN) / (VOLTAGE_BAT_MAX - VOLTAGE_BAT_MIN);
}

void Battery::print() {
  Serial.println(
    "⚡ Battery: Vin:" + String(this->get_vin()) + 
    " Vbat:" + String(this->get_vbat()) +
    " Usage:" + String(this->get_percentage()) + "%");
}
