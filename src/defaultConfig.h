#ifndef DEFAULT_CONF_H
#define DEFAULT_CONF_H
#include <Arduino.h>

#define SW_VERSION "1.0.3"

#define SMOGGY_I2C_THP_ADDR 0x76

extern bool DEBUG;
extern char DEVICENAME[32];
extern char AQI_ECO_PATH[64];
extern unsigned int DUST_NUMBEROFMEASUREMENTS;
extern int BAT_NUMBEROFMEASUREMENTS;
extern int BAT_DELAY;
extern unsigned int MEASURMENT_INTERVAL;

#endif