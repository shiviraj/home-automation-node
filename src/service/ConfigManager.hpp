#ifndef CONFIG_MANAGER_HPP
#define CONFIG_MANAGER_HPP

#include <ESP8266WebServer.h>
#include <logger/Logger.hpp>
#include <service/MemoryService.hpp>

class ConfigManager
{
private:
    MemoryService *memory;

public:
    ConfigManager();
    ConfigManager(MemoryService &memory);
    ConfigManager &setMemory(MemoryService &memory);

    void init();
    String getSSID();
    String getPassword();
    String getHost();
    String getUsername();
    String getPass();
};

#endif