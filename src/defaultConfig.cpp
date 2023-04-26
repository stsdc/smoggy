#include "defaultConfig.h"


char DEVICENAME[32]  = "Smoggy";

char AQI_ECO_PATH[64] = "/u/???";
bool DEBUG            = true;

unsigned int DUST_NUMBEROFMEASUREMENTS = 10;

// Number of samples to get to measure average battery voltage
int BAT_NUMBEROFMEASUREMENTS = 50;

// Delay between getting each sample of battery voltage in ms
int BAT_DELAY = 20;

unsigned int MEASURMENT_INTERVAL = 120e3; // in ms
