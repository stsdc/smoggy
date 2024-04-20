#include "Aqieco.hpp"

Aqieco::Aqieco() : httpClient() {
  httpClient.setTimeout(20000);
  httpClient.setReuse(false);
}

String Aqieco::buildJSON(
  signed short& averagePM1,
  signed short& averagePM25,
  signed short& averagePM10,
  float         & temperature,
  float         & pressure,
  float         & humidity,
  Battery       & battery
  ) {
  StaticJsonDocument<768> jsonBuffer;
  JsonObject json = jsonBuffer.to<JsonObject>();

  json["esp8266id"]        = this->smoggy_id;
  json["software_version"] = "Smoggy " + String(SW_VERSION);

  JsonArray  sensordatavalues = json.createNestedArray("sensordatavalues");
  JsonObject P0               = sensordatavalues.createNestedObject();
  P0["value_type"] = "PMS_P0";
  (averagePM1 == -1) ? P0["value"] = "" : P0["value"] = averagePM1;

  JsonObject P1 = sensordatavalues.createNestedObject();
  P1["value_type"] = "PMS_P1";
  (averagePM10 == -1) ? P1["value"] = "" : P1["value"] = averagePM10;

  JsonObject P2 = sensordatavalues.createNestedObject();
  P2["value_type"] = "PMS_P2";
  (averagePM25 == -1) ? P2["value"] = "" : P2["value"] = averagePM25;


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
  jsonBatteryVoltage["value"]      = String(battery.vbat); // V
  
  JsonObject jsonBatteryPercentage = sensordatavalues.createNestedObject();
  jsonBatteryPercentage["value_type"] = "battery_percentage";
  jsonBatteryPercentage["value"]      = String(battery.get_percentage()); // %

  String requestBody;
  serializeJson(json, requestBody);
  return requestBody;
}

void Aqieco::setup(String smoggy_id) {
    this->smoggy_id = smoggy_id;
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
        httpClient.setUserAgent(this->smoggy_id);
        httpClient.addHeader("X-Sensor", this->smoggy_id);
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
    signed short & averagePM1,
    signed short & averagePM25,
    signed short & averagePM10,
    float & temperature,
    float & pressure,
    float & humidity,
    Battery & battery) {
        this->sendRequest(
            this->buildJSON(averagePM1, averagePM25, averagePM10, temperature, pressure, humidity, battery),
            1, HOST_AQIECO, PORT_AQIECO, AQI_ECO_PATH);
    return true;
};