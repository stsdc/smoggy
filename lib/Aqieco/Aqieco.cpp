#include "Aqieco.hpp"

Aqieco::Aqieco() : httpClient() {
  httpClient.setTimeout(20000);
  httpClient.setReuse(false);
}

String Aqieco::buildJSON(
  unsigned short& averagePM1,
  unsigned short& averagePM25,
  unsigned short& averagePM10,
  float         & temperature,
  float         & pressure,
  float         & humidity,
  Battery       & battery
  ) {
  StaticJsonDocument<768> jsonBuffer;
  JsonObject json = jsonBuffer.to<JsonObject>();

  json["esp8266id"]        = String((uint32_t)(ESP.getEfuseMac()));
  json["software_version"] = "Smoggy 1.0.0-beta";

  JsonArray  sensordatavalues = json.createNestedArray("sensordatavalues");
  JsonObject P0               = sensordatavalues.createNestedObject();
  P0["value_type"] = "PMS_P0";
  P0["value"]      = averagePM1;
  JsonObject P1 = sensordatavalues.createNestedObject();
  P1["value_type"] = "PMS_P1";
  P1["value"]      = averagePM10;
  JsonObject P2 = sensordatavalues.createNestedObject();
  P2["value_type"] = "PMS_P2";
  P2["value"]      = averagePM25;

  JsonObject jsonTemperature = sensordatavalues.createNestedObject();
  jsonTemperature["value_type"] = "BME280_temperature";
  jsonTemperature["value"]      = String(temperature);

  JsonObject jsonHumidity = sensordatavalues.createNestedObject();
  jsonHumidity["value_type"] = "BME280_humidity";
  jsonHumidity["value"]      = String(humidity);

  JsonObject jsonPressure = sensordatavalues.createNestedObject();
  jsonPressure["value_type"] = "BME280_pressure";
  jsonPressure["value"]      = String(pressure * 100); // hPa -> Pa


  JsonObject jsonBatteryVoltage = sensordatavalues.createNestedObject();
  jsonBatteryVoltage["value_type"] = "battery_voltage";
  jsonBatteryVoltage["value"]      = String(battery.get_vbat()); // V
  
  JsonObject jsonBatteryPercentage = sensordatavalues.createNestedObject();
  jsonBatteryPercentage["value_type"] = "battery_percentage";
  jsonBatteryPercentage["value"]      = String(battery.get_percentage()); // %

  String requestBody;
  serializeJson(json, requestBody);
  return requestBody;
}

bool Aqieco::sendRequest(
    String json,
    const int pin,
    const String &host,
    const int port,
    const String &url
    ) {
    Serial.println("Sending request - " + String(host));
    if (httpClient.begin(host, port, url)) {
        httpClient.addHeader("Content-Type", "application/json");
        httpClient.addHeader("X-PIN", String(pin));
        httpClient.setUserAgent("smogomierz-" + String((uint32_t)(ESP.getEfuseMac())));
        httpClient.addHeader("X-Sensor", "smogomierz-" + String((uint32_t)(ESP.getEfuseMac())));
        auto result = httpClient.POST(json);
        if (result >= HTTP_CODE_OK && result <= HTTP_CODE_ALREADY_REPORTED) {
            Serial.println("Succeeded - " + String(result));
        } else {
            Serial.println("Failed - " + String(result));
        }
    } else {
        Serial.println("Failed to connect");
    }
    httpClient.end();
    return true;
}

bool Aqieco::send(
    unsigned short & averagePM1,
    unsigned short & averagePM25,
    unsigned short & averagePM10,
    float & temperature,
    float & pressure,
    float & humidity,
    Battery & battery) {
        this->sendRequest(
            this->buildJSON(averagePM1, averagePM25, averagePM10, temperature, pressure, humidity, battery),
            1, HOST_AQIECO, PORT_AQIECO, AQI_ECO_PATH);
    return true;
};