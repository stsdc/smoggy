#include "Webpage.hpp"

AutoConnectInput   aqiecoPathInput("aqiecoPath", AQI_ECO_PATH, "aqi.eco update path");
AutoConnectElement hr("element", "<hr>");
ACSubmit(saveSubmit, "SAVE", "/save");

String smid = "Device ID: smogomierz-" + String((uint32_t)(ESP.getEfuseMac()));
AutoConnectText smoggyIdText("text", smid.c_str(), "display:block;");

SmoggyPortal::SmoggyPortal() : server(), portal(server), config() {}

void SmoggyPortal::setup() {
  config.homeUri = "/";
  config.bootUri = AC_ONBOOTURI_HOME;
  config.hostName = "Smoggy";
  config.apid     = "Smoggy";
  config.title    = "Smoggy";

  config.autoReconnect = true;
  portal.config(config); // Don't forget.

  smoggy_main_page = AutoConnectAux("/", "Smoggy", true, { smoggyIdText, aqiecoPathInput, saveSubmit });
  smoggy_main_page[F("aqiecoPath")].as<AutoConnectInput>().value = AQI_ECO_PATH;
  portal.join(smoggy_main_page);

  server.on("/save", [&](){

    sprintf(AQI_ECO_PATH, server.arg("aqiecoPath").c_str());
    saveConfig();
    smoggy_main_page[F("aqiecoPath")].as<AutoConnectInput>().value = AQI_ECO_PATH;
    
    server.sendHeader("Location", String("http://") + server.client().localIP().toString() + String("/"));
    server.send(302, "text/plain", "");
    server.client().flush();
    server.client().stop();
  });

  if (portal.begin()) {
    Serial.println(
      "Access: http://" + WiFi.localIP().toString() + " or http://" + config.hostName + ".local");

    if (MDNS.begin("Smoggy")) {
      MDNS.addService("http", "tcp", 80);
    }
  }
}

