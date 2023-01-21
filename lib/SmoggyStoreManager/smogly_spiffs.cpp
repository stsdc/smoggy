
#include "smogly_spiffs.hpp"


void _safeCpy(char* dest, const JsonVariant &obj, const char* dflt = "", int CharSize = 255) {
  const char* val = obj.as<const char*>();
  if (val) {
    strncpy(dest, val, CharSize);
  } else {
    strncpy(dest, dflt, CharSize);
  }
}

bool loadConfig() {
#ifdef ARDUINO_ARCH_ESP8266
  File configFile = SPIFFS.open("/config.json", "r");
#elif defined ARDUINO_ARCH_ESP32
  File configFile = SPIFFS.open("/config.json");
#endif

  if (!configFile) {
    Serial.println(F("Failed to open config file"));
    return false;
  }

  size_t size = configFile.size();
  if (size > 2048) {
    Serial.println(F("Config file size is too large"));
    return false;
  }

  // Allocate a buffer to store contents of the file.
  std::unique_ptr<char[]> buf(new char[size]);

  // We don't use String here because ArduinoJson library requires the input
  // buffer to be mutable. If you don't use ArduinoJson, you may as well
  // use configFile.readString instead.
  configFile.readBytes(buf.get(), size);

  //StaticJsonDocument<capacity> jsonBuffer;
#ifdef ARDUINO_ARCH_ESP8266
  const short capacity = 6144;
  StaticJsonDocument<capacity> jsonBuffer;
  // DynamicJsonDocument jsonBuffer(ESP.getMaxFreeBlockSize());
#elif defined ARDUINO_ARCH_ESP32
  // const short capacity = 4608;
  // const short capacity = 5620;
  // StaticJsonDocument<capacity> jsonBuffer;
  DynamicJsonDocument jsonBuffer(ESP.getMaxAllocHeap());
#endif

  deserializeJson(jsonBuffer, buf.get());
  JsonObject json = jsonBuffer.as<JsonObject>();

  if (json.isNull()) {
    Serial.println(F("Failed to parse config file"));
    return false;
  }

  // REMEMBER TO ADD/EDIT KEYS IN defaultConfig.hpp AND webserver.h!!
  _safeCpy(AQI_ECO_PATH, json["AQI_ECO_PATH"], "path", 64);

  // Real world application would store these values in some variables for
  // later use.
    if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
      Serial.print(F("Loaded AQI_ECO_PATH: "));
      Serial.println(AQI_ECO_PATH);

      Serial.println(F("\n"));
#elif defined ARDUINO_ARCH_ESP32
      Serial.print("Loaded AQI_ECO_PATH: ");
      Serial.println(AQI_ECO_PATH);

      Serial.println("\n");
#endif
    }
    return true;
  }

bool saveConfig() {

#ifdef ARDUINO_ARCH_ESP8266
  const short capacity = 6144;
  StaticJsonDocument<capacity> jsonBuffer;
  // DynamicJsonDocument jsonBuffer(ESP.getMaxFreeBlockSize());
#elif defined ARDUINO_ARCH_ESP32
  // const short capacity = 4608;
  // const short capacity = 5620;
  // StaticJsonDocument<capacity> jsonBuffer;
  DynamicJsonDocument jsonBuffer(ESP.getMaxAllocHeap());  
#endif


  JsonObject json = jsonBuffer.to<JsonObject>();


  json["AQI_ECO_PATH"] = String(AQI_ECO_PATH);


#ifdef ARDUINO_ARCH_ESP8266
  File configFile = SPIFFS.open("/config.json", "w");
#elif defined ARDUINO_ARCH_ESP32
  File configFile = SPIFFS.open("/config.json", FILE_WRITE);
#endif

  if (!configFile) {
#ifdef ARDUINO_ARCH_ESP8266
    Serial.println(F("Failed to open config file for writing"));
#elif defined ARDUINO_ARCH_ESP32
    Serial.println(("Failed to open config file for writing"));
#endif
    return false;
  }

  serializeJson(json, configFile);
  if (DEBUG) {
#ifdef ARDUINO_ARCH_ESP8266
    Serial.println(F("config saved"));
#elif defined ARDUINO_ARCH_ESP32
    Serial.println(("config saved"));
#endif
  }
  return true;
}

void fs_setup() {
#ifdef ARDUINO_ARCH_ESP32
  delay(10);
#endif

#ifdef ARDUINO_ARCH_ESP8266
  Serial.println(F("Mounting FS..."));
  if (!SPIFFS.begin()) {
    Serial.println(F("Failed to mount file system"));
    return;
  }
#elif defined ARDUINO_ARCH_ESP32
  Serial.println(("Mounting FS..."));
  if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
    Serial.println(("SPIFFS Mount Failed"));
    return;
  }
#endif

#ifdef ARDUINO_ARCH_ESP8266
  if (!loadConfig()) {
    Serial.println(F("Failed to load config"));
    Serial.println(F("Saving the current config..."));
    saveConfig();
  } else {
    Serial.println(F("Config loaded"));
  }
#elif defined ARDUINO_ARCH_ESP32
  if (!loadConfig()) {
    Serial.println(("Failed to load config"));
    Serial.println(("Saving the current config..."));
    saveConfig();
  } else {
    Serial.println(("Config loaded"));
  }
#endif


}

void deleteConfig() {
  SPIFFS.remove("/config.json");
}
