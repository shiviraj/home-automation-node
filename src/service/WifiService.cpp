#include <service/WifiService.hpp>

WiFiService::WiFiService()
{
    WiFi.mode(WIFI_STA);
}

WiFiService::WiFiService(ConfigManager &configManager)
{
    setConfigManager(configManager);
    WiFi.mode(WIFI_STA);
}

WiFiService &WiFiService::setConfigManager(ConfigManager &configManager)
{
    this->configManager = &configManager;
    return *this;
}

wl_status_t WiFiService::autoConnect()
{
    if (!connected())
    {
        logger.info("Connecting WiFi with SSID : " + configManager->getSSID());
        WiFi.begin(configManager->getSSID(), configManager->getPassword());
    }
    return WiFi.status();
}

void WiFiService::setupAP(String node)
{
    WiFi.softAP(node, "home-automation");
    logger.info("Neither Wifi nor Mqtt is connected");
    logger.info("Starting Access Point as " + node);
}

bool WiFiService::connected()
{
    return WiFi.waitForConnectResult() == WL_CONNECTED;
}