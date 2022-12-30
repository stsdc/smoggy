
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
      Serial.print(F("Loaded DEVICENAME_AUTO: "));
      Serial.println(DEVICENAME_AUTO);
      Serial.print(F("Loaded DEVICENAME: "));
      Serial.println(DEVICENAME);
      Serial.print(F("Loaded LANGUAGE: "));
      Serial.println(LANGUAGE);
      Serial.print(F("Loaded SELECTED_LANGUAGE: "));
      Serial.println(SELECTED_LANGUAGE);

      Serial.print(F("Loaded THP_MODEL: "));
      Serial.println(THP_MODEL);
      Serial.print(F("Loaded DUST_MODEL: "));
      Serial.println(DUST_MODEL);
      Serial.print(F("Loaded DISPLAY_PM1: "));
      Serial.println(DISPLAY_PM1);
      Serial.print(F("Loaded FREQUENTMEASUREMENT: "));
      Serial.println(FREQUENTMEASUREMENT);

      Serial.print(F("Loaded SECOND_THP: "));
      Serial.println(SECOND_THP_MODEL);
      Serial.print(F("Loaded SECOND_THP_MODEL: "));
      Serial.println(SECOND_THP_MODEL);

      Serial.print(F("Loaded FIRST_THP_SDA: "));
      Serial.println(FIRST_THP_SDA);
      Serial.print(F("Loaded FIRST_THP_SCL: "));
      Serial.println(FIRST_THP_SCL);

      Serial.print(F("Loaded SECOND_THP_SDA: "));
      Serial.println(SECOND_THP_SDA);
      Serial.print(F("Loaded SECOND_THP_SCL: "));
      Serial.println(SECOND_THP_SCL);

      Serial.print(F("Loaded DUST_TX: "));
      Serial.println(DUST_TX);
      Serial.print(F("Loaded DUST_RX: "));
      Serial.println(DUST_RX);

      Serial.print(F("Loaded CONFIG_FIRST_THP_SDA: "));
      Serial.println(CONFIG_FIRST_THP_SDA);
      Serial.print(F("Loaded CONFIG_FIRST_THP_SCL: "));
      Serial.println(CONFIG_FIRST_THP_SCL);

      Serial.print(F("Loaded CONFIG_SECOND_THP_SDA: "));
      Serial.println(CONFIG_SECOND_THP_SDA);
      Serial.print(F("Loaded CONFIG_SECOND_THP_SCL: "));
      Serial.println(CONFIG_SECOND_THP_SCL);

      Serial.print(F("Loaded CONFIG_DUST_TX: "));
      Serial.println(CONFIG_DUST_TX);
      Serial.print(F("Loaded CONFIG_DUST_RX: "));
      Serial.println(CONFIG_DUST_RX);

      Serial.print(F("Loaded DUST_TIME: "));
      Serial.println(DUST_TIME);
      Serial.print(F("Loaded NUMBEROFMEASUREMENTS: "));
      Serial.println(NUMBEROFMEASUREMENTS);

      Serial.print(F("Loaded LUFTDATEN_ON: "));
      Serial.println(LUFTDATEN_ON);
      Serial.print(F("Loaded LUFTDATEN_GRAPH_ON: "));
      Serial.println(LUFTDATEN_GRAPH_ON);
	  
      Serial.print(F("Loaded SMOGLIST_ON: "));
      Serial.println(SMOGLIST_ON);

      Serial.print(F("Loaded AIRMONITOR_ON: "));
      Serial.println(AIRMONITOR_ON);
      Serial.print(F("Loaded AIRMONITOR_GRAPH_ON: "));
      Serial.println(AIRMONITOR_GRAPH_ON);
      Serial.print(F("Loaded AIRMONITOR_API_KEY: "));
      Serial.println(AIRMONITOR_API_KEY);
      Serial.print(F("Loaded LATITUDE: "));
      Serial.println(LATITUDE);
      Serial.print(F("Loaded LONGITUDE: "));
      Serial.println(LONGITUDE);
      Serial.print(F("Loaded EMAIL: "));
      Serial.println(EMAIL);
      Serial.print(F("Loaded MYALTITUDE: "));
      Serial.println(MYALTITUDE);

      Serial.print(F("Loaded THINGSPEAK_ON: "));
      Serial.println(THINGSPEAK_ON);
      Serial.print(F("Loaded THINGSPEAK_GRAPH_ON: "));
      Serial.println(THINGSPEAK_GRAPH_ON);
      Serial.print(F("Loaded THINGSPEAK_API_KEY: "));
      Serial.println(THINGSPEAK_API_KEY);
      Serial.print(F("Loaded THINGSPEAK_CHANNEL_ID: "));
      Serial.println(THINGSPEAK_CHANNEL_ID);
      Serial.print(F("Loaded THINGSPEAK_READ_API_KEY: "));
      Serial.println(THINGSPEAK_READ_API_KEY);

      Serial.print(F("Loaded INFLUXDB_ON: "));
      Serial.println(INFLUXDB_ON);
      Serial.print(F("Loaded INFLUXDB_VERSION: "));
      Serial.println(INFLUXDB_VERSION);
      Serial.print(F("Loaded INFLUXDB_HOST: "));
      Serial.println(INFLUXDB_HOST);
      Serial.print(F("Loaded INFLUXDB_PORT: "));
      Serial.println(INFLUXDB_PORT);
      Serial.print(F("Loaded INFLUXDB_DATABASE: "));
      Serial.println(INFLUXDB_DATABASE);
      Serial.print(F("Loaded INFLUXDB_USER: "));
      Serial.println(INFLUXDB_USER);
      Serial.print(F("Loaded INFLUXDB_PASSWORD: "));
      Serial.println(INFLUXDB_PASSWORD);
      Serial.print(F("Loaded INFLUXDB_ORG: "));
      Serial.println(INFLUXDB_ORG);
      Serial.print(F("Loaded INFLUXDB_BUCKET: "));
      Serial.println(INFLUXDB_BUCKET);
      Serial.print(F("Loaded INFLUXDB_TOKEN: "));
      Serial.println(INFLUXDB_TOKEN);

      Serial.print(F("Loaded MQTT_ON: "));
      Serial.println(MQTT_ON);
      Serial.print(F("Loaded MQTT_HOST: "));
      Serial.println(MQTT_HOST);
      Serial.print(F("Loaded MQTT_PORT: "));
      Serial.println(MQTT_PORT);
      Serial.print(F("Loaded MQTT_USER: "));
      Serial.println(MQTT_USER);
      Serial.print(F("Loaded MQTT_PASSWORD: "));
      Serial.println(MQTT_PASSWORD);

      Serial.print(F("Loaded MQTT_IP_IN_TOPIC: "));
      Serial.println(MQTT_IP_IN_TOPIC);
      Serial.print(F("Loaded MQTT_DEVICENAME_IN_TOPIC: "));
      Serial.println(MQTT_DEVICENAME_IN_TOPIC);
      Serial.print(F("Loaded MQTT_SLASH_AT_THE_BEGINNING: "));
      Serial.println(MQTT_SLASH_AT_THE_BEGINNING);
      Serial.print(F("Loaded MQTT_SLASH_AT_THE_END: "));
      Serial.println(MQTT_SLASH_AT_THE_END);

      Serial.print(F("Loaded MQTT_TOPIC_TEMP: "));
      Serial.println(MQTT_TOPIC_TEMP);
      Serial.print(F("Loaded MQTT_TOPIC_HUMI: "));
      Serial.println(MQTT_TOPIC_HUMI);
      Serial.print(F("Loaded MQTT_TOPIC_PRESS: "));
      Serial.println(MQTT_TOPIC_PRESS);
      Serial.print(F("Loaded MQTT_TOPIC_PM1: "));
      Serial.println(MQTT_TOPIC_PM1);
      Serial.print(F("Loaded MQTT_TOPIC_PM25: "));
      Serial.println(MQTT_TOPIC_PM25);
      Serial.print(F("Loaded MQTT_TOPIC_PM10: "));
      Serial.println(MQTT_TOPIC_PM10);
      Serial.print(F("Loaded MQTT_TOPIC_AIRQUALITY: "));
      Serial.println(MQTT_TOPIC_AIRQUALITY);

      Serial.print(F("Loaded AQI_ECO_ON: "));
      Serial.println(AQI_ECO_ON);
      Serial.print(F("Loaded AQI_ECO_HOST: "));
      Serial.println(AQI_ECO_HOST);
      Serial.print(F("Loaded AQI_ECO_PATH: "));
      Serial.println(AQI_ECO_PATH);

      Serial.print(F("Loaded SENDING_FREQUENCY: "));
      Serial.println(SENDING_FREQUENCY);
      Serial.print(F("Loaded SENDING_DB_FREQUENCY: "));
      Serial.println(SENDING_DB_FREQUENCY);
      Serial.print(F("Loaded DEEPSLEEP_ON: "));
      Serial.println(DEEPSLEEP_ON);

      Serial.print(F("Loaded DEBUG: "));
      Serial.println(DEBUG);
      Serial.print(F("Loaded AUTOUPDATE_ON: "));
      Serial.println(AUTOUPDATE_ON);

      Serial.print(F("Loaded CONFIG_AUTH: "));
      Serial.println(CONFIG_AUTH);
      Serial.print(F("Loaded CONFIG_USERNAME: "));
      Serial.println(CONFIG_USERNAME);
      Serial.print(F("Loaded CONFIG_PASSWORD: "));
      Serial.println(CONFIG_PASSWORD);

      Serial.print(F("Loaded MODEL: "));
      Serial.println(MODEL);

      Serial.print(F("Loaded HOMEKIT_SUPPORT: "));
      Serial.println(HOMEKIT_SUPPORT);

      Serial.print(F("Loaded PMSENSORVERSION: "));
      Serial.println(PMSENSORVERSION);

      Serial.print(F("Loaded SOFTWAREVERSION: "));
      Serial.println(SOFTWAREVERSION);

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
