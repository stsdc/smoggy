#include "DustSensor.h"

// static float calib = 1;

DustSensor::DustSensor(int PIN_RX, int PIN_TX) : hw_serial(1), pms(hw_serial){
  this->pin_rx = PIN_RX;
  this->pin_tx = PIN_TX;
}

void DustSensor::setup(unsigned short number_of_measurments = 10) {
  this->number_of_measurments = number_of_measurments;
  this->measurements = new DustSample[number_of_measurments];

    hw_serial.begin(9600, SERIAL_8N1, this->pin_rx, this->pin_tx); //PMSx003 serial
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

DustSensor::DustSample DustSensor::getAverage() {
    averageDustSample.PM1 = 0;
    averageDustSample.PM2_5 = 0;
    averageDustSample.PM4 = 0;
    averageDustSample.PM10 = 0;

    for (int i = 0; i < this->number_of_measurments; i++) {
        averageDustSample.PM1 += this->measurements[i].PM1;
        averageDustSample.PM2_5 += this->measurements[i].PM2_5;
        averageDustSample.PM10 += this->measurements[i].PM10;
    }
    averageDustSample.PM1 = averageDustSample.PM1 / this->number_of_measurments;
    averageDustSample.PM2_5 = averageDustSample.PM2_5 / this->number_of_measurments;
    averageDustSample.PM10 = averageDustSample.PM10 / this->number_of_measurments;

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

bool DustSensor::getMeasurements() {

  if (DEBUG) {
    Serial.println(("Turning ON PM sensor..."));
  }

    this->pms.wakeUp();
    this->pms.requestRead();

  int counterNM1 = 0;
  while (counterNM1 < this->number_of_measurments) {
    Serial.println(("Trying to read PM data..."));
    if (pms.readUntil(data)) {
      this->processMeasurement(counterNM1);
      counterNM1++;
    } else {
      Serial.println(("No response from PM sensor..."));
      return false;
    }
  }
  if (DEBUG) {
    Serial.println(("Turning OFF PM sensor...\n"));
  }

    this->pms.sleep();
  return true;
}

DustSensor::DustSample DustSensor::getDust() {
  if (this->getMeasurements()) {
    return this->getAverage();
  }
  DustSample dustSample;
  dustSample.PM1 = -1;
  dustSample.PM2_5 = -1;
  dustSample.PM10 = -1;
  return dustSample;
}