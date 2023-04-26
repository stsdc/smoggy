#pragma once

#include <Arduino.h>
#include "esp_adc_cal.h"

#define R1 33
#define R2 100
#define VOLTAGE_OUT(Vin) (((Vin) * R2) / (R1 + R2))
#define VOLTAGE_BAT_MAX 4.0
#define VOLTAGE_BAT_MIN 3.3
#define ADC_REFERENCE 3.3
#define VOLTAGE_TO_ADC(in) ((ADC_REFERENCE * (in)) / 4096)
#define BATTERY_MAX_ADC VOLTAGE_TO_ADC(VOLTAGE_OUT(VOLTAGE_BAT_MAX))
#define BATTERY_MIN_ADC VOLTAGE_TO_ADC(VOLTAGE_OUT(VOLTAGE_BAT_MIN))
#define PIN_ADC_BAT 33
class Battery {
    public:
        Battery();
        float vin;
        float vbat;
        void sampling_on(int, int);
        void sampling_off();
        float get_percentage();
        void print();

};