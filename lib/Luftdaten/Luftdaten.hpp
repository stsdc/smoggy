#include <ArduinoJson.h>

#ifdef ARDUINO_ARCH_ESP8266
#include <ESP8266HTTPClient.h>
#elif defined ARDUINO_ARCH_ESP32
#include <WiFi.h>
#include <HTTPClient.h>
#endif


#define HOST_MADAVI "api-rrd.madavi.de"
#define URL_MADAVI "/data.php"
#define PORT_MADAVI 80

#define HOST_SENSORCOMMUNITY "api.sensor.community"
#define URL_SENSORCOMMUNITY "/v1/push-sensor-data/"
#define PORT_SENSORCOMMUNITY 80

class Luftdaten {
    public:
        Luftdaten();
        void setup();
        bool send(
    unsigned short & averagePM1,
    unsigned short & averagePM25,
    unsigned short & averagePM10,
    float & temperature,
    float & pressure,
    float & humidity);
    
    private:
        HTTPClient httpClient;
        String buildDustJSON(unsigned short & averagePM1, unsigned short & averagePM25, unsigned short & averagePM10);
        String buildMadaviDustJSON(unsigned short & averagePM1, unsigned short & averagePM25, unsigned short & averagePM10);
        String buildTHPJSON(float & temperature, float & humidity, float & pressure);
        bool sendDustRequest(String);
        bool sendTHPRequest(String);
        bool sendRequest(
            String json,
            const int pin,
            const String &host,
            const int port,
            const String &url
            );
};