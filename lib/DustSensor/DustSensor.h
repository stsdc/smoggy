#ifndef DUST_H
#define DUST_H

#include <Arduino.h>
#include "../../src/defaultConfig.h"

// #include "../include/defaultConfig.hpp"

// #ifdef ASYNC_WEBSERVER_ON
// #include <AsyncTCP.h>
// #include <ESPAsyncWebServer.h>
// #else
// #include <WebServer.h>
// #endif

// #ifdef ASYNC_WEBSERVER_ON
// #include "../lib/smogly_asyncwebserver.hpp"
// #else
// // #include "../lib/smogly_webserver.hpp"
// #endif



#define DUSTSENSOR_PMS5003_7003_BME280_0x76 // PMS5003 / PMS7003 - BME280_0x76
// #define DUSTSENSOR_PMS5003_7003_BME280_0x77 // PMS5003 / PM§S7003 - BME280_0x77
// #define DUSTSENSOR_SDS011_21 // Nova Fitness SDS011 / SDS021
// #define DUSTSENSOR_HPMA115S0 // Honeywell HPMA115S0
// #define DUSTSENSOR_SPS30 // Sensirion SPS30

#include "PMS.h" // https://github.com/fu-hsi/PMS // 5.11.2021
//   unsigned char iPM = 0;

class DustSensor {
    public:
        void calibrate(float, float);
        void setup(unsigned short number_of_measurments);
        void read();
        void processMeasurement(int);
        void takeSleepPMMeasurements();
        struct DustSample{
            unsigned short PM1;
            unsigned short PM2_5;
            unsigned short PM4; // DUSTSENSOR_SPS30
            unsigned short PM10;
        } averageDustSample;

        DustSample get_average();

        unsigned int previous_2sec_Millis;
        unsigned short TwoSec_interval;
        DustSensor();

    private:
        PMS::DATA data;
        HardwareSerial hw_serial; // Change TX - D5 and RX - D4 pins
        PMS pms;
        DustSample *measurements;
        float calibration_magic_value;
        unsigned short number_of_measurments;
        unsigned char iPM;

};
#endif