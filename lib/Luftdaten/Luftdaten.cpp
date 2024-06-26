#include "Luftdaten.hpp"

Luftdaten::Luftdaten() : httpClient(){
    httpClient.setTimeout(20000);
    httpClient.setReuse(false);
};

void Luftdaten::setup(String smoggy_id) {
    this->smoggy_id = smoggy_id;
}


bool Luftdaten::send(
    signed short & averagePM1,
    signed short & averagePM25,
    signed short & averagePM10,
    float & temperature,
    float & pressure,
    float & humidity) {
        this->sendRequest(
            this->buildDustJSON(averagePM1, averagePM25, averagePM10),
            1, HOST_SENSORCOMMUNITY, PORT_SENSORCOMMUNITY, URL_SENSORCOMMUNITY);

        this->sendRequest(
            this->buildMadaviDustJSON(averagePM1, averagePM25, averagePM10),
            1, HOST_MADAVI, PORT_MADAVI, URL_MADAVI);

        this->sendRequest(
            this->buildTHPJSON(temperature, humidity, pressure),
            11, HOST_SENSORCOMMUNITY, PORT_SENSORCOMMUNITY, URL_SENSORCOMMUNITY);

        this->sendRequest(
            this->buildTHPJSON(temperature, humidity, pressure),
            11, HOST_MADAVI, PORT_MADAVI, URL_MADAVI);
    return true;
};

bool Luftdaten::sendRequest(
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

String Luftdaten::buildDustJSON(signed short & averagePM1, signed short & averagePM25, signed short & averagePM10) {
    StaticJsonDocument<600> jsonBuffer;
    JsonObject json = jsonBuffer.to<JsonObject>();
    json["software_version"] = "Smoggy " + String(SW_VERSION);
    JsonArray sensordatavalues = json.createNestedArray("sensordatavalues");
      JsonObject P0 = sensordatavalues.createNestedObject();
      P0["value_type"] = "P0";
      (averagePM1 == -1) ? P0["value"] = "" : P0["value"] = averagePM1;
      JsonObject P1 = sensordatavalues.createNestedObject();
      P1["value_type"] = "P1";
      (averagePM10 == -1) ? P1["value"] = "" : P1["value"] = averagePM10;
      JsonObject P2 = sensordatavalues.createNestedObject();
      P2["value_type"] = "P2";
      (averagePM25 == -1) ? P2["value"] = "" : P2["value"] = averagePM25;

        String requestBody;
        serializeJson(json, requestBody);
        return requestBody;
}

String Luftdaten::buildMadaviDustJSON(signed short & averagePM1, signed short & averagePM25, signed short & averagePM10) {
    StaticJsonDocument<600> jsonBuffer;
    JsonObject json = jsonBuffer.to<JsonObject>();
    json["software_version"] = "Smoggy " + String(SW_VERSION);
    JsonArray sensordatavalues = json.createNestedArray("sensordatavalues");
      JsonObject P0 = sensordatavalues.createNestedObject();
      P0["value_type"] = "PMS_P0";
      P0["value"] = averagePM1;
      JsonObject P1 = sensordatavalues.createNestedObject();
      P1["value_type"] = "PMS_P1"; // Could be also SDS_P1 or HPM_P1 for a respective sensor
      P1["value"] = averagePM10;
      JsonObject P2 = sensordatavalues.createNestedObject();
      P2["value_type"] = "PMS_P2"; // Could be also SDS_P2 or HPM_P2 for a respective sensor
      P2["value"] = averagePM25;

        String requestBody;
        serializeJson(json, requestBody);
        return requestBody;
}

String Luftdaten::buildTHPJSON(float & temperature, float & humidity, float & pressure) {
    StaticJsonDocument<600> jsonBuffer;
    JsonObject json = jsonBuffer.to<JsonObject>();
    json["software_version"] = "Smoggy " + String(SW_VERSION);
    JsonArray sensordatavalues = json.createNestedArray("sensordatavalues");
      JsonObject jsonTemperature = sensordatavalues.createNestedObject();
      jsonTemperature["value_type"] = "temperature";
      jsonTemperature["value"] = String(temperature);
      JsonObject jsonHumidity = sensordatavalues.createNestedObject();
      jsonHumidity["value_type"] = "humidity";
      jsonHumidity["value"] = String(humidity);
      JsonObject jsonPressure = sensordatavalues.createNestedObject();
      jsonPressure["value_type"] = "pressure";
      jsonPressure["value"] = String(pressure * 100); //hPa -> Pa

        String requestBody;
        serializeJson(json, requestBody);
        return requestBody;
}