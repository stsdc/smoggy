#include <ArduinoJson.h>
#include <FS.h>
#ifdef ARDUINO_ARCH_ESP32
#include <SPIFFS.h>
#endif
#include "../../src/defaultConfig.h"
#define FORMAT_SPIFFS_IF_FAILED true

bool loadConfig();
bool saveConfig();

void fs_setup();
void deleteConfig();