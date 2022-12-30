#include "DustSensor.h"

// static float calib = 1;

DustSensor::DustSensor() : hw_serial(1), pms(hw_serial){
}

void DustSensor::setup(unsigned short number_of_measurments) {
  this->number_of_measurments = number_of_measurments;
  this->measurements = new DustSample[number_of_measurments];

    hw_serial.begin(9600, SERIAL_8N1, 16, 17); //PMSx003 serial
    // if (FREQUENTMEASUREMENT == true) {
    //     this->pms.wakeUp();
    //     delay(500);
    //     this->pms.activeMode();
    // } else {
      pms.passiveMode();
      delay(500);
      this->pms.sleep();
    // }
}

void DustSensor::calibrate(float temperature, float humidity) {
    if (int(temperature) < 5 or int(humidity) > 60) {
        this->calibration_magic_value = float((200 - (humidity)) / 150) / 2;
      }
      this->calibration_magic_value = 1.0;
}

void DustSensor::read() {
    this->pms.read(this->data);
    // Serial.print("PM 1.0 (ug/m3): ");
    // Serial.println(this->data.PM_AE_UG_1_0);

    // Serial.print("PM 2.5 (ug/m3): ");
    // Serial.println(this->data.PM_AE_UG_2_5);

    // Serial.print("PM 10.0 (ug/m3): ");
    // Serial.println(this->data.PM_AE_UG_10_0);
}

DustSensor::DustSample DustSensor::get_average() {
    averageDustSample.PM1 = 0;
    averageDustSample.PM2_5 = 0;
    averageDustSample.PM4 = 0;
    averageDustSample.PM10 = 0;

    for (int i = 0; i < NUMBEROFMEASUREMENTS; i++) {
        averageDustSample.PM1 += this->measurements[i].PM1;
        averageDustSample.PM2_5 += this->measurements[i].PM2_5;
        averageDustSample.PM10 += this->measurements[i].PM10;
    }
    averageDustSample.PM1 = averageDustSample.PM1 / NUMBEROFMEASUREMENTS;
    averageDustSample.PM2_5 = averageDustSample.PM2_5 / NUMBEROFMEASUREMENTS;
    averageDustSample.PM10 = averageDustSample.PM10 / NUMBEROFMEASUREMENTS;

    if (DEBUG) {
        Serial.print(("\n"));
        Serial.println(("=========AVERAGE========="));
        Serial.println(("Average PM1: " + String(this->averageDustSample.PM1)));
        Serial.println(("Average PM2.5: " + String(this->averageDustSample.PM2_5)));
        Serial.print(("\n"));

    }
    return averageDustSample;
}

void DustSensor::processMeasurement(int counter) {
  /*
    #ifdef DUSTSENSOR_SPS30
    unsigned short pmMeasurements[9][3];
    #else
    unsigned short pmMeasurements[9][2];
    #endif
  */
  DustSample dustSample;
  dustSample.PM1 = this->calibration_magic_value * data.PM_AE_UG_1_0;
  dustSample.PM2_5 = this->calibration_magic_value * data.PM_AE_UG_2_5;
  dustSample.PM10 = this->calibration_magic_value * data.PM_AE_UG_10_0;

  this->measurements[counter] = dustSample;

  if (DEBUG) {
    Serial.println("#" + String(counter + 1) +
      " measurement: PM1: " + String(this->measurements[counter].PM1) +
      " PM2.5: " + String(this->measurements[counter].PM2_5) +
      " PM10: " + String(this->measurements[counter].PM10)
      );

  }

}

void DustSensor::takeSleepPMMeasurements() {

  if (DEBUG) {
    Serial.println(("Turning ON PM sensor..."));
  }

    this->pms.wakeUp();
    this->pms.requestRead();

  int counterNM1 = 0;
  while (counterNM1 < this->number_of_measurments) {
    if (pms.readUntil(data)) {
      this->processMeasurement(counterNM1);
      counterNM1++;
    }
  }
  if (DEBUG) {
    Serial.println(("Turning OFF PM sensor...\n"));
  }

    this->pms.sleep();

}


