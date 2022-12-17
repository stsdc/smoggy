#if defined(ESP8266)
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#else
#include <WiFi.h>
#endif

#include <ESPAsyncWebServer.h>     //Local WebServer used to serve the configuration portal
#include <ESPAsyncWiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic


#define SSID "Aura"

// void setup_wifi();
// void configModeCallback(WiFiManager *wifi_manager);

class WiFiManager {
    public:
        WiFiManager();
        static boolean isAP;

        boolean isConnected();
        void setup();
    
    private:
        AsyncWiFiManager asyncWifiManager;
        static void configModeCallback(AsyncWiFiManager *asyncWifiManager);

};