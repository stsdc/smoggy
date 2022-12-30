#include <ESPmDNS.h>
#include <AutoConnect.h>
#include <smogly_spiffs.hpp>

#include "../../src/defaultConfig.h"
// WebServer   Server;
// AutoConnect portal(Server);
// AutoConnectConfig config = AutoConnectConfig();

class SmoggyPortal {
  public:
    SmoggyPortal();
    WebServer server;
    AutoConnect portal;
    AutoConnectConfig config;
    void setup();
    void savePage();
    AutoConnectAux smoggy_main_page;

};

void savePage();