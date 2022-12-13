#include "Dust.h"
#include"../lib/providers/TemperatureHumidityPressure.h"

static float calib = 1;


void pm_calibration() {
  // Automatic calibration - START
  if (!strcmp(MODEL, "white")) {
    if (!strcmp(THP_MODEL, "BME280")) {

#ifdef ARDUINO_ARCH_ESP8266
      BMESensor.refresh(FIRST_THP_SDA, FIRST_THP_SCL);
      if (int(BMESensor.temperature) < 5 or int(BMESensor.humidity) > 60) {
        calib1 = float((200 - (BMESensor.humidity)) / 150);
        calib2 = calib1 / 2;
        calib = calib2;
      } else {
        calib = calib1;
      }
#elif defined ARDUINO_ARCH_ESP32
      if (int(bme.readTemperature()) < 5 or int(bme.readHumidity()) > 60) {
        calib1 = float((200 - (bme.readHumidity())) / 150);
        calib2 = calib1 / 2;
        calib = calib2;
      } else {
        calib = calib1;
      }
#endif
    } else if (!strcmp(THP_MODEL, "HTU21")) {
      if (int(ht2x.readTemperature()) < 5 or int(ht2x.getCompensatedHumidity(int(ht2x.readTemperature()))) > 60) {
        calib1 = float((200 - (ht2x.getCompensatedHumidity(int(ht2x.readTemperature())))) / 150);
        calib2 = calib1 / 2;
        calib = calib2;
      } else {
        calib = calib1;
      }
    } else if (!strcmp(THP_MODEL, "DHT22")) {
      if (int(dht.readTemperature()) < 5 or int(dht.readHumidity()) > 60) {
        calib1 = float((200 - (dht.readHumidity())) / 150);
        calib2 = calib1 / 2;
        calib = calib2;
      } else {
        calib = calib1;
      }
    } else if (!strcmp(THP_MODEL, "SHT1x")) {
      if (int(sht1x.readTemperatureC()) < 5 or int(sht1x.readHumidity()) > 60) {
        calib1 = float((200 - (sht1x.readHumidity())) / 150);
        calib2 = calib1 / 2;
        calib = calib2;
      } else {
        calib = calib1;
      }
    }

  }
  // Automatic calibration - END

  if (!strcmp(THP_MODEL, "BME280")) {
    calib = calib1;
  } else if (!strcmp(THP_MODEL, "HTU21")) {
    calib = calib1;
  } else if (!strcmp(THP_MODEL, "DHT22")) {
    calib = calib1;
  } else if (!strcmp(THP_MODEL, "SHT1x")) {
    calib = calib1;
  } else if (!strcmp(THP_MODEL, "BMP280")) {
    calib = calib1;
  } else if (!strcmp(THP_MODEL, "DS18B20")) {
    calib = calib1;
  }

}


void averagePM() {
  averagePM1 = 0;
  averagePM25 = 0;
  averagePM10 = 0;
#ifdef DUSTSENSOR_SPS30
  averagePM4 = 0;
#endif
  for (int i = 0; i < NUMBEROFMEASUREMENTS; i++) {
    averagePM1 += pmMeasurements[i][0];
    averagePM25 += pmMeasurements[i][1];
    averagePM10  += pmMeasurements[i][2];
#ifdef DUSTSENSOR_SPS30
    averagePM4 += pmMeasurements[i][3];
#endif
  }
  averagePM1 = averagePM1 / NUMBEROFMEASUREMENTS;
  averagePM25 = averagePM25 / NUMBEROFMEASUREMENTS;
  averagePM10 = averagePM10 / NUMBEROFMEASUREMENTS;
#ifdef DUSTSENSOR_SPS30
  averagePM4 = averagePM4 / NUMBEROFMEASUREMENTS;
#endif
  if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
    Serial.print(F("\n"));
    Serial.print(F("========================================"));
    Serial.print(F("\n\nAverage PM1: "));
    Serial.print(averagePM1);
    Serial.print(F("\nAverage PM2.5: "));
    Serial.print(averagePM25);
#ifdef DUSTSENSOR_SPS30
    Serial.print(F("\nAverage PM4: "));
    Serial.print(averagePM4);
#endif
    Serial.print(F("\nAverage PM10: "));
    Serial.print(averagePM10);
    Serial.print(F("\n\n"));
    Serial.print(F("========================================"));
    Serial.print(F("\n"));
#elif defined ARDUINO_ARCH_ESP32
    Serial.print(("\n"));
    Serial.print(("========================================"));
    Serial.print(("\n\nAverage PM1: "));
    Serial.print(averagePM1);
    Serial.print(("\nAverage PM2.5: "));
    Serial.print(averagePM25);
#ifdef DUSTSENSOR_SPS30
    Serial.print(("\nAverage PM4: "));
    Serial.print(averagePM4);
#endif
    Serial.print(("\nAverage PM10: "));
    Serial.print(averagePM10);
    Serial.print(("\n\n"));
    Serial.print(("========================================"));
    Serial.print(("\n"));
#endif
  }

#ifdef ARDUINO_ARCH_ESP32
  if (HOMEKIT_SUPPORT) {
    // homekit_DeviceData.homekit_pm10_level = averagePM10;
    // homekit_DeviceData.homekit_pm25_level = averagePM25;
    // notify_hap();
  }
#endif
}

void takeNormalnPMMeasurements() {
  /*
    #ifdef DUSTSENSOR_SPS30
    unsigned short pmMeasurements[9][3];
    #else
    unsigned short pmMeasurements[9][2];
    #endif
  */
  // unsigned char iPM = 0;

#ifdef DUSTSENSOR_PMS5003_7003_BME280_0x76 or DUSTSENSOR_PMS5003_7003_BME280_0x77
  pmMeasurements[iPM][0] = (calib * data.PM_AE_UG_1_0);
  pmMeasurements[iPM][1] = (calib * data.PM_AE_UG_2_5);
  pmMeasurements[iPM][2] = (calib * data.PM_AE_UG_10_0);
#elif defined DUSTSENSOR_SDS011_21
#ifdef ARDUINO_ARCH_ESP8266
  PmResult SDSdata = sds.queryPm();
#ifndef ASYNC_WEBSERVER_ON
  delay(1000);
#endif
  if (SDSdata.isOk()) {
    pmMeasurements[iPM][0] = (calib * 0);
    pmMeasurements[iPM][1] = (calib * SDSdata.pm25);
    pmMeasurements[iPM][2] = (calib * SDSdata.pm10);
  } else {
#ifdef ARDUINO_ARCH_ESP8266
    Serial.println(F("\nCould not read values from SDS sensor :( "));
#elif defined ARDUINO_ARCH_ESP32
    Serial.println(("\nCould not read values from SDS sensor :( "));
#endif
  }
#elif defined ARDUINO_ARCH_ESP32
  err = my_sds.read(&SDSpm25, &SDSpm10);
  if (!err) {
    pmMeasurements[iPM][0] = (calib * 0);
    pmMeasurements[iPM][1] = (calib * SDSpm25);
    pmMeasurements[iPM][2] = (calib * SDSpm10);
  } else {
#ifdef ARDUINO_ARCH_ESP8266
    Serial.println(F("\nCould not read values from SDS sensor :( "));
#elif defined ARDUINO_ARCH_ESP32
    Serial.println(("\nCould not read values from SDS sensor :( "));
#endif
  }
#endif
#elif defined DUSTSENSOR_HPMA115S0
  if (hpma115S0.ReadParticleMeasurement(&hpma115S0_pm25, &hpma115S0_pm10)) {
    if (hpma115S0_pm25 == 0 and hpma115S0_pm10 == 0) {
#ifndef ASYNC_WEBSERVER_ON
      delay(100);
#endif
      hpma115S0.ReadParticleMeasurement(&hpma115S0_pm25, &hpma115S0_pm10);
      pmMeasurements[iPM][0] = (calib * 0);
      pmMeasurements[iPM][1] = (calib * hpma115S0_pm25);
      pmMeasurements[iPM][2] = (calib * hpma115S0_pm10);
    } else {
      pmMeasurements[iPM][0] = (calib * 0);
      pmMeasurements[iPM][1] = (calib * hpma115S0_pm25);
      pmMeasurements[iPM][2] = (calib * hpma115S0_pm10);
    }
  }
#elif defined DUSTSENSOR_SPS30
  read_sps30_data();

  pmMeasurements[iPM][0] = (calib * SPS30_PM1);
  pmMeasurements[iPM][1] = (calib * SPS30_PM25);
  pmMeasurements[iPM][2] = (calib * SPS30_PM10);
  pmMeasurements[iPM][3] = (calib * SPS30_PM4);

#else // If no dust sensor has been defined - use DUSTSENSOR_PMS5003_7003_BME280_0x76
  pmMeasurements[iPM][0] = (calib * data.PM_AE_UG_1_0);
  pmMeasurements[iPM][1] = (calib * data.PM_AE_UG_2_5);
  pmMeasurements[iPM][2] = (calib * data.PM_AE_UG_10_0);
#endif

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
    Serial.print(pmMeasurements[iPM][0]);
    Serial.print(("\nValue of PM2.5: "));
    Serial.print(pmMeasurements[iPM][1]);
#ifdef DUSTSENSOR_SPS30
    Serial.print(("\nValue of PM4: "));
    Serial.print(pmMeasurements[iPM][3]);
#endif
    Serial.print(("\nValue of PM10: "));
    Serial.println(pmMeasurements[iPM][2]);
#endif

  }
  if (++iPM == NUMBEROFMEASUREMENTS) {
    averagePM();
    iPM = 0;
  }

}

void takeSleepPMMeasurements() {
  if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
    Serial.print(F("\nTurning ON PM sensor..."));
#elif defined ARDUINO_ARCH_ESP32
    Serial.print(("\nTurning ON PM sensor..."));
#endif
  }

#ifdef DUSTSENSOR_PMS5003_7003_BME280_0x76 or DUSTSENSOR_PMS5003_7003_BME280_0x77 // PMSx003
  if (!strcmp(DUST_MODEL, "PMS7003")) {
    pms.wakeUp();
#ifndef ASYNC_WEBSERVER_ON
    unsigned int current_2sec_Millis = millis();
    previous_2sec_Millis = millis();
    while (previous_2sec_Millis - current_2sec_Millis <= TwoSec_interval * 5) {
      WebServer.handleClient();
      previous_2sec_Millis = millis();
    }
    previous_2sec_Millis = 0;
#endif
    pms.requestRead();
  }

  int counterNM1 = 0;
  while (counterNM1 < NUMBEROFMEASUREMENTS) {
#ifdef ASYNC_WEBSERVER_ON
    if (pms.readUntil(data)) {
      takeNormalnPMMeasurements();
      counterNM1++;
    }
#else
    unsigned int current_2sec_Millis = millis();
    if (current_2sec_Millis - previous_2sec_Millis >= TwoSec_interval) {

      if (pms.readUntil(data)) {
        takeNormalnPMMeasurements();
        counterNM1++;
      }

      previous_2sec_Millis = millis();
    }
    WebServer.handleClient();
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
    pms.sleep();
  }
#elif defined DUSTSENSOR_SDS011_21 // SDSx1
  if (!strcmp(DUST_MODEL, "SDS011/21")) {
#ifdef ARDUINO_ARCH_ESP8266
    sds.wakeup();
    sds.setQueryReportingMode().toString(); // ensures sensor is in 'query' reporting mode
    sds.setContinuousWorkingPeriod().toString(); // ensures sensor has continuous working period - default but not recommended
#elif defined ARDUINO_ARCH_ESP32

#endif

#ifndef ASYNC_WEBSERVER_ON
    unsigned int current_2sec_Millis = millis();
    previous_2sec_Millis = millis();
    while (previous_2sec_Millis - current_2sec_Millis <= TwoSec_interval * 10) {
      WebServer.handleClient();
      previous_2sec_Millis = millis();
    }
    previous_2sec_Millis = 0;
#endif
  }

  int counterNM1 = 0;
  while (counterNM1 < NUMBEROFMEASUREMENTS) {
#ifdef ASYNC_WEBSERVER_ON
#ifdef ARDUINO_ARCH_ESP8266
    PmResult SDSdata = sds.queryPm();
#endif
    takeNormalnPMMeasurements();
    counterNM1++;
#else
    unsigned int current_2sec_Millis = millis();
    if (current_2sec_Millis - previous_2sec_Millis >= TwoSec_interval) {
#ifdef ARDUINO_ARCH_ESP8266
      PmResult SDSdata = sds.queryPm();
#elif defined ARDUINO_ARCH_ESP32
#endif
      delay(1000);
      takeNormalnPMMeasurements();
      counterNM1++;
      previous_2sec_Millis = millis();
    }
    WebServer.handleClient();
    delay(10);
#endif
  }
  if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
    Serial.print(F("\nTurning OFF PM sensor...\n"));
#elif defined ARDUINO_ARCH_ESP32
    Serial.print(("\nTurning OFF PM sensor...\n"));
#endif
  }

  if (!strcmp(DUST_MODEL, "SDS011/21")) {
#ifdef ARDUINO_ARCH_ESP8266
    sds.setCustomWorkingPeriod(1);
    WorkingStateResult state = sds.sleep();
#elif defined ARDUINO_ARCH_ESP32

#endif
  }
#elif defined DUSTSENSOR_HPMA115S0
  if (!strcmp(DUST_MODEL, "HPMA115S0")) {
    hpma115S0.Init();
#ifndef ASYNC_WEBSERVER_ON
    delay(10);
#endif
    hpma115S0.EnableAutoSend();
#ifndef ASYNC_WEBSERVER_ON
    delay(10);
#endif
    hpma115S0.StartParticleMeasurement();

#ifndef ASYNC_WEBSERVER_ON
    unsigned int current_2sec_Millis = millis();
    previous_2sec_Millis = millis();
    while (previous_2sec_Millis - current_2sec_Millis <= TwoSec_interval * 8) {
      WebServer.handleClient();
      delay(10);
      previous_2sec_Millis = millis();
    }
    previous_2sec_Millis = 0;
#endif
  }
  int counterNM1 = 0;
  while (counterNM1 < NUMBEROFMEASUREMENTS) {
#ifdef ASYNC_WEBSERVER_ON
    if (hpma115S0.ReadParticleMeasurement(&hpma115S0_pm25, &hpma115S0_pm10)) {
      takeNormalnPMMeasurements();
      counterNM1++;
    }
#else
    unsigned int current_2sec_Millis = millis();
    if (current_2sec_Millis - previous_2sec_Millis >= TwoSec_interval) {
      if (hpma115S0.ReadParticleMeasurement(&hpma115S0_pm25, &hpma115S0_pm10)) {
        takeNormalnPMMeasurements();
        counterNM1++;
      }
      previous_2sec_Millis = millis();
    }
    WebServer.handleClient();
    delay(10);
#endif
  }
  if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
    Serial.print(F("\nTurning OFF PM sensor...\n"));
#elif defined ARDUINO_ARCH_ESP32
    Serial.print(("\nTurning OFF PM sensor...\n"));
#endif
  }

  if (!strcmp(DUST_MODEL, "HPMA115S0")) {
    hpma115S0.DisableAutoSend();
#ifndef ASYNC_WEBSERVER_ON
    delay(10);
#endif
    hpma115S0.StopParticleMeasurement();
  }
#elif defined DUSTSENSOR_SPS30
  if (!strcmp(DUST_MODEL, "SPS30")) {

    // WAKE UP SPS30!!
    sps30.wakeup();
#ifndef ASYNC_WEBSERVER_ON
    delay(100);
#endif
    // reset SPS30 connection

    if (sps30.reset() == false) {
      Errorloop((char *) "could not reset.", 0);
    }

#ifndef ASYNC_WEBSERVER_ON
    unsigned int current_2sec_Millis = millis();
    previous_2sec_Millis = millis();
    while (previous_2sec_Millis - current_2sec_Millis <= TwoSec_interval * 8) {
      WebServer.handleClient();
      delay(10);
      previous_2sec_Millis = millis();
    }
    previous_2sec_Millis = 0;
#endif
  }
  int counterNM1 = 0;
  while (counterNM1 < NUMBEROFMEASUREMENTS) {
#ifdef ASYNC_WEBSERVER_ON
    takeNormalnPMMeasurements();
    counterNM1++;
#else
    unsigned int current_2sec_Millis = millis();
    if (current_2sec_Millis - previous_2sec_Millis >= TwoSec_interval) {

      takeNormalnPMMeasurements();
      counterNM1++;

      previous_2sec_Millis = millis();
    }
    WebServer.handleClient();
    delay(10);
#endif
  }
  if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
    Serial.print(F("\nTurning OFF PM sensor...\n"));
#elif defined ARDUINO_ARCH_ESP32
    Serial.print(("\nTurning OFF PM sensor...\n"));
#endif
  }

  if (!strcmp(DUST_MODEL, "SPS30")) {
    // GO TO SLEEP SPS30!!
    sps30.sleep();
  }
#else // If no dust sensor has been defined - use DUSTSENSOR_PMS5003_7003_BME280_0x76
  if (!strcmp(DUST_MODEL, "PMS7003")) {
    pms.wakeUp();
#ifndef ASYNC_WEBSERVER_ON
    unsigned int current_2sec_Millis = millis();
    previous_2sec_Millis = millis();
    while (previous_2sec_Millis - current_2sec_Millis <= TwoSec_interval * 5) {
      WebServer.handleClient();
      previous_2sec_Millis = millis();
    }
    previous_2sec_Millis = 0;
#endif
    pms.requestRead();
  }

  int counterNM1 = 0;
  while (counterNM1 < NUMBEROFMEASUREMENTS) {
#ifdef ASYNC_WEBSERVER_ON
    if (pms.readUntil(data)) {
      takeNormalnPMMeasurements();
      counterNM1++;
    }
#else
    unsigned int current_2sec_Millis = millis();
    if (current_2sec_Millis - previous_2sec_Millis >= TwoSec_interval) {

      if (pms.readUntil(data)) {
        takeNormalnPMMeasurements();
        counterNM1++;
      }

      previous_2sec_Millis = millis();
    }
    WebServer.handleClient();
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
    pms.sleep();
  }
#endif

}


#ifdef DUSTSENSOR_SPS30
bool read_sps30_data()
{

  static bool header = true;
  uint8_t ret, error_cnt = 0;
  struct sps_values val;

  // loop to get data
  do {

    ret = sps30.GetValues(&val);

    // data might not have been ready
    if (ret == ERR_DATALENGTH) {

      if (error_cnt++ > 3) {
        ErrtoMess("Error during reading values: ", ret);
        return (false);
      }
#ifdef ASYNC_WEBSERVER_ON
      /*
            time_now_temp = millis();
            while (millis() < time_now_temp + 1000) {
              //wait approx. 1000 ms
            }
      */
      yield();
#else
      delay(1000);
#endif
    }

    // if other error
    else if (ret != SPS30_ERR_OK) {
      ErrtoMess("Error during reading values: ", ret);
      return (false);
    }

  } while (ret != SPS30_ERR_OK);


  SPS30_PM1 = val.MassPM1;
  SPS30_PM25 = val.MassPM2;
  SPS30_PM4 = val.MassPM4;
  SPS30_PM10 = val.MassPM10;

  /*
    pmMeasurements[iPM][0] = int(calib * SPS30_PM1);
    pmMeasurements[iPM][1] = int(calib * SPS30_PM25);
    pmMeasurements[iPM][2] = int(calib * SPS30_PM10);
    pmMeasurements[iPM][3] = int(calib * SPS30_PM4);
  */
  return (true);
}

void GetDeviceInfo()
{
  char buf[32];
  uint8_t ret;
  SPS30_version v;

  //try to read serial number
  ret = sps30.GetSerialNumber(buf, 32);
  if (ret == SPS30_ERR_OK) {
#ifdef ARDUINO_ARCH_ESP8266
    Serial.print(F("Serial number: "));
#elif defined ARDUINO_ARCH_ESP32
    Serial.print(("Serial number: "));
#endif
    if (strlen(buf) > 0)  Serial.println(buf);
    else Serial.println(("not available"));
  }
  else
    ErrtoMess((char *) "could not get serial number ", ret);

  // try to get product name
  ret = sps30.GetProductName(buf, 32);
  if (ret == SPS30_ERR_OK)  {
#ifdef ARDUINO_ARCH_ESP8266
    Serial.print(F("Product name: "));
#elif defined ARDUINO_ARCH_ESP32
    Serial.print(("Product name: "));
#endif
    if (strlen(buf) > 0)  Serial.println(buf);
    else Serial.println(("not available"));
  }
  else
    ErrtoMess((char *) "could not get product name ", ret);

  // try to get version info
  ret = sps30.GetVersion(&v);
  if (ret != SPS30_ERR_OK) {
#ifdef ARDUINO_ARCH_ESP8266
    Serial.println(F("Can not read version info"));
#elif defined ARDUINO_ARCH_ESP32
    Serial.println(("Can not read version info"));
#endif
    return;
  }

#ifdef ARDUINO_ARCH_ESP8266
  Serial.print(F("Firmware level: "));
  Serial.print(v.major);
  Serial.print(F("."));
  Serial.println(v.minor);

  if (SP30_COMMS != I2C_COMMS) {
    Serial.print(F("Hardware level: "));
    Serial.println(v.HW_version);

    Serial.print(F("SHDLC protocol: "));
    Serial.print(v.SHDLC_major);
    Serial.print(F("."));
    Serial.println(v.SHDLC_minor);
  }

  Serial.print(F("Library level: "));
  Serial.print(v.DRV_major);
  Serial.print(F("."));
  Serial.println(v.DRV_minor);
#elif defined ARDUINO_ARCH_ESP32
  Serial.print(("Firmware level: "));
  Serial.print(v.major);
  Serial.print(("."));
  Serial.println(v.minor);

  if (SP30_COMMS != I2C_COMMS) {
    Serial.print(("Hardware level: "));
    Serial.println(v.HW_version);

    Serial.print(("SHDLC protocol: "));
    Serial.print(v.SHDLC_major);
    Serial.print(("."));
    Serial.println(v.SHDLC_minor);
  }

  Serial.print(("Library level: "));
  Serial.print(v.DRV_major);
  Serial.print(("."));
  Serial.println(v.DRV_minor);
#endif
}


void SetAutoClean()
{
  uint32_t interval;
  uint8_t ret;

  // try to get interval
  ret = sps30.GetAutoCleanInt(&interval);
  if (ret == SPS30_ERR_OK) {
#ifdef ARDUINO_ARCH_ESP8266
    Serial.print(F("Current Auto Clean interval: "));
    Serial.print(interval);
    Serial.println(F(" seconds"));
#elif defined ARDUINO_ARCH_ESP32
    Serial.print(("Current Auto Clean interval: "));
    Serial.print(interval);
    Serial.println((" seconds"));
#endif
  }
  else
    ErrtoMess((char *) "could not get clean interval ", ret);

  // only if requested
  if (SPS30_AUTOCLEANINTERVAL == -1) {
#ifdef ARDUINO_ARCH_ESP8266
    Serial.println(F("No Auto Clean interval change requested"));
#elif defined ARDUINO_ARCH_ESP32
    Serial.println(("No Auto Clean interval change requested"));
#endif
    return;
  }

  // try to set interval
  interval = SPS30_AUTOCLEANINTERVAL;
  ret = sps30.SetAutoCleanInt(interval);
  if (ret == SPS30_ERR_OK) {
#ifdef ARDUINO_ARCH_ESP8266
    Serial.print(F("Auto Clean interval now set: "));
    Serial.print(interval);
    Serial.println(F(" seconds"));
#elif defined ARDUINO_ARCH_ESP32
    Serial.print(("Auto Clean interval now set: "));
    Serial.print(interval);
    Serial.println((" seconds"));
#endif
  }
  else
    ErrtoMess((char *) "could not set clean interval ", ret);

  // try to get interval
  ret = sps30.GetAutoCleanInt(&interval);
  if (ret == SPS30_ERR_OK) {
#ifdef ARDUINO_ARCH_ESP8266
    Serial.print(F("Current Auto Clean interval: "));
    Serial.print(interval);
    Serial.println(F(" seconds"));
#elif defined ARDUINO_ARCH_ESP32
    Serial.print(("Current Auto Clean interval: "));
    Serial.print(interval);
    Serial.println((" seconds"));
#endif
  }
  else
    ErrtoMess((char *) "could not get clean interval ", ret);
}

void Errorloop(char *mess, uint8_t r)
{
  if (r) ErrtoMess(mess, r);
  else Serial.println(mess);
  //Serial.println(F("Program on hold"));
  //for (;;) delay(100000);
}

void ErrtoMess(char *mess, uint8_t r)
{
  char buf[80];
  Serial.print(mess);
  sps30.GetErrDescription(r, buf, 80);
  Serial.println(buf);
}

#endif