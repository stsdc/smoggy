#include "DustSensor.h"

// static float calib = 1;

DustSensor::DustSensor() : hw_serial(1), pms(hw_serial){
}

void DustSensor::setup(bool FREQUENTMEASUREMENT) {
    unsigned int previous_2sec_Millis = 0;
    unsigned short TwoSec_interval = 2 * 1000; // 2 second

    hw_serial.begin(9600, SERIAL_8N1, DUST_TX, DUST_RX); //PMSx003 serial
    if (FREQUENTMEASUREMENT == true) {
        this->pms.wakeUp();
        delay(500);
        this->pms.activeMode();
    } else {
      pms.passiveMode();
      delay(500);
      this->pms.sleep();
    }
}

void DustSensor::calibrate(float temperature, float humidity) {
    if (int(temperature) < 5 or int(humidity) > 60) {
        this->calibration_magic_value = float((200 - (humidity)) / 150) / 2;
      }
      this->calibration_magic_value = 1.0;
}

void DustSensor::read() {
    this->pms.read(this->data);
}

void DustSensor::get_average(int NUMBEROFMEASUREMENTS) {
    averageDustSample.PM1 = 0;
    averageDustSample.PM2_5 = 0;
    averageDustSample.PM4 = 0;
    averageDustSample.PM10 = 0;

    for (int i = 0; i < NUMBEROFMEASUREMENTS; i++) {
        averageDustSample.PM1 += this->measurements[i][0];
        averageDustSample.PM2_5 += this->measurements[i][1];
        averageDustSample.PM10 += this->measurements[i][2];
    }
    averageDustSample.PM1 = averageDustSample.PM1 / NUMBEROFMEASUREMENTS;
    averageDustSample.PM2_5 = averageDustSample.PM2_5 / NUMBEROFMEASUREMENTS;
    averageDustSample.PM10 = averageDustSample.PM10 / NUMBEROFMEASUREMENTS;

    if (DEBUG) {
        Serial.print(("\n"));
        Serial.print(("========================================"));
        Serial.print(("\n\nAverage PM1: "));
        Serial.print(averagePM1);
        Serial.print(("\nAverage PM2.5: "));
        Serial.print(averagePM25);
    }
}

void DustSensor::takeNormalnPMMeasurements() {
  /*
    #ifdef DUSTSENSOR_SPS30
    unsigned short pmMeasurements[9][3];
    #else
    unsigned short pmMeasurements[9][2];
    #endif
  */
  // unsigned char iPM = 0;

  this->measurements[iPM][0] = (this->calibration_magic_value * data.PM_AE_UG_1_0);
  this->measurements[iPM][1] = (this->calibration_magic_value * data.PM_AE_UG_2_5);
  this->measurements[iPM][2] = (this->calibration_magic_value * data.PM_AE_UG_10_0);


  if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
    Serial.print(F("\n\nPM measurement number: "));
    Serial.print(iPM);
    Serial.print(F("\nValue of PM1: "));
    Serial.print(pmMeasurements[iPM][0]);
    Serial.print(F("\nValue of PM2.5: "));
    Serial.print(pmMeasurements[iPM][1]);
#ifdef DUSTSENSOR_SPS30
    Serial.print(F("\nValue of PM4: "));
    Serial.print(pmMeasurements[iPM][3]);
#endif
    Serial.print(F("\nValue of PM10: "));
    Serial.println(pmMeasurements[iPM][2]);
#elif defined ARDUINO_ARCH_ESP32
    Serial.print(("\n\nPM measurement number: "));
    Serial.print(iPM);
    Serial.print(("\nValue of PM1: "));
    Serial.print(this->measurements[iPM][0]);
    Serial.print(("\nValue of PM2.5: "));
    Serial.print(this->measurements[iPM][1]);
#ifdef DUSTSENSOR_SPS30
    Serial.print(("\nValue of PM4: "));
    Serial.print(this->measurements[iPM][3]);
#endif
    Serial.print(("\nValue of PM10: "));
    Serial.println(this->measurements[iPM][2]);
#endif

  }
  if (++iPM == NUMBEROFMEASUREMENTS) {
    this->get_average(NUMBEROFMEASUREMENTS);
    iPM = 0;
  }

}

void DustSensor::takeSleepPMMeasurements() {
//   if (DEBUG) {
// #ifdef ARDUINO_ARCH_ESP8266
//     Serial.print(F("\nTurning ON PM sensor..."));
// #elif defined ARDUINO_ARCH_ESP32
//     Serial.print(("\nTurning ON PM sensor..."));
// #endif
//   }

//   if (!strcmp(DUST_MODEL, "PMS7003")) {
    this->pms.wakeUp();
// #ifndef ASYNC_WEBSERVER_ON
//     unsigned int current_2sec_Millis = millis();
//     previous_2sec_Millis = millis();
//     while (previous_2sec_Millis - current_2sec_Millis <= TwoSec_interval * 5) {
//       // WebServer.handleClient();
//       previous_2sec_Millis = millis();
//     }
//     previous_2sec_Millis = 0;
// #endif
    this->pms.requestRead();
//   }

  int counterNM1 = 0;
  while (counterNM1 < NUMBEROFMEASUREMENTS) {
#ifdef ASYNC_WEBSERVER_ON
    if (pms.readUntil(data)) {
      takeNormalnPMMeasurements();
      counterNM1++;
    }
#else
    unsigned int current_2sec_Millis = millis();
    if (current_2sec_Millis - this->previous_2sec_Millis >= TwoSec_interval) {

      if (pms.readUntil(this->data)) {
        this->takeNormalnPMMeasurements();
        counterNM1++;
      }

       this->previous_2sec_Millis = millis();
    }
    // WebServer.handleClient();
#endif
  }
  if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
    Serial.print(F("\nTurning OFF PM sensor...\n"));
#elif defined ARDUINO_ARCH_ESP32
    Serial.print(("\nTurning OFF PM sensor...\n"));
#endif
  }

  if (!strcmp(DUST_MODEL, "PMS7003")) {
    this->pms.sleep();
  }
}
