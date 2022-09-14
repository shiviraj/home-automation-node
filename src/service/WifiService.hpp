#ifndef WIFI_SERVICE_HPP
#define WIFI_SERVICE_HPP

#include <service/ConfigManager.hpp>
#include <logger/Logger.hpp>
#include <ESP8266WiFi.h>

class WiFiService
{
private:
    ConfigManager *configManager;
    Logger logger;
    WiFiService &setConfigManager(ConfigManager &ConfigManager);

public:
    WiFiService();
    WiFiService(ConfigManager &ConfigManager);
    wl_status_t autoConnect();
    void setupAP(String node);
    bool connected();
};

#endif