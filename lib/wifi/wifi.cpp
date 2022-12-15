#include "wifi.hpp"

// void configModeCallback (WiFiManager *wifi_manager) {
//   Serial.println("Entered config mode");
//   Serial.println(WiFi.softAPIP());

//   Serial.println(wifi_manager->getConfigPortalSSID());
// }

// void setup_wifi() {
//   WiFiManager wifiManager;
//   wifiManager.setAPCallback(configModeCallback);
//   wifiManager.autoConnect(SSID);
// }

WIFI::WIFI(){}


void WIFI::setup() {
    wifiManager.setConnectTimeout(5);
    wifiManager.setConfigPortalTimeout(15);
    wifiManager.setAPCallback(this->configModeCallback);
    wifiManager.setSTAStaticIPConfig(IPAddress(192,168,1,103), IPAddress(192,168,1,1), IPAddress(255,255,255,0));
    wifiManager.autoConnect(SSID);
}

boolean WIFI::isConnected() {
    if (WiFi.status() == WL_CONNECTED) {
        return true;
    }
    return false;
}


void WIFI::configModeCallback (WiFiManager *wifi_manager) {
  Serial.println(WiFi.softAPIP());
  Serial.println(wifi_manager->getConfigPortalSSID());
}