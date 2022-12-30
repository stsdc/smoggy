#include <ArduinoJson.h>

#include <SmoggyBattery.hpp>

#ifdef ARDUINO_ARCH_ESP8266
#include <ESP8266HTTPClient.h>
#elif defined ARDUINO_ARCH_ESP32
#include <WiFi.h>
#include <HTTPClient.h>
#endif

#include "../../src/defaultConfig.h"

#define HOST_AQIECO "api.aqi.eco"
#define PORT_AQIECO 80


class Aqieco {
    public:
        Aqieco();
        void setup();
        bool send(
    unsigned short & averagePM1,
    unsigned short & averagePM25,
    unsigned short & averagePM10,
    float & temperature,
    float & pressure,
    float & humidity,
    Battery & battery);
    
    private:
        HTTPClient httpClient;
        String buildJSON(unsigned short & averagePM1, unsigned short & averagePM25, unsigned short & averagePM10, float & temperature, float & humidity, float & pressure, Battery & battery);
        bool sendRequest(
            String json,
            const int pin,
            const String &host,
            const int port,
            const String &url
            );
};