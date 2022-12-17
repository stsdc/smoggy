#include "WiFiManager.hpp"

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

AsyncWebServer server(80);
DNSServer dns;

WiFiManager::WiFiManager() : asyncWifiManager(&server, &dns){}

void WiFiManager::configModeCallback (AsyncWiFiManager *asyncWifiManager) {
  Serial.println(WiFi.softAPIP());
  Serial.println(asyncWifiManager->getConfigPortalSSID());
}

void WiFiManager::setup() {
    asyncWifiManager.setConnectTimeout(5);
    asyncWifiManager.setConfigPortalTimeout(15);
    asyncWifiManager.setAPCallback(this->configModeCallback);
    asyncWifiManager.setSTAStaticIPConfig(IPAddress(192,168,1,103), IPAddress(192,168,1,1), IPAddress(255,255,255,0));
    asyncWifiManager.autoConnect(SSID);
}

boolean WiFiManager::isConnected() {
    if (WiFi.status() == WL_CONNECTED) {
        return true;
    }
    return false;
}


