#include <WiFi.h>
#include <WiFiManager.h>

#define SSID "Aura"

// void setup_wifi();
// void configModeCallback(WiFiManager *wifi_manager);

class WIFI {
    public:
        WIFI();
        static boolean isAP;

        boolean isConnected();
        void setup();
    
    private:
        WiFiManager wifiManager;
        static void configModeCallback(WiFiManager *wifi_manager);

};