#include "SmoggyBattery.hpp"

Battery::Battery() {
}

float Battery::get_vin() {
    int adcSum = 0;
    int num_of_samples = 50;
    for (int i = 0; i < num_of_samples; i++) {
        adcSum += analogRead(PIN_ADC_BAT);
        delay(50);
    }

    auto vin = ((adcSum/num_of_samples) * ADC_REFERENCE) / (4095);
    Serial.println("⚡ Battery: Vin: " + String(vin));
  return vin;
}

float Battery::get_vbat() {
    auto vbat = ((R1 + R2) * this->get_vin()) / R2;
    Serial.println("⚡ Battery: Vbat: " + String(vbat));
  return vbat;
}

float Battery::get_percentage() {
    auto percentage = 100 * (this->get_vbat() - VOLTAGE_BAT_MIN) / (VOLTAGE_BAT_MAX - VOLTAGE_BAT_MIN);
    Serial.println("⚡ Battery: " + String(percentage)) + "%%";
  return percentage;
}

void Battery::print() {
  Serial.println(
    "⚡ Battery: Vin:" + String(this->get_vin()) + 
    " Vbat:" + String(this->get_vbat()) +
    " Usage:" + String(this->get_percentage()) + "%");
}
