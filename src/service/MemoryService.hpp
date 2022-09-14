#ifndef MEMORY_SERVICE_HPP
#define MEMORY_SERVICE_HPP

#include <EEPROM.h>
#include <logger/Logger.hpp>

class MemoryService
{

private:
    int variables = 5;
    int memorySize = 64;
    Logger logger;

public:
    String ssid, password, host, username, pass;
    MemoryService();
    void setVars(String ssid, String password, String host, String username, String pass);
};

#endif