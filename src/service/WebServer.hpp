#ifndef WEB_SERVER_HPP
#define WEB_SERVER_HPP

#include <ESP8266WebServer.h>
#include <service/MemoryService.hpp>
#include <logger/Logger.hpp>

class WebServer
{
private:
    ESP8266WebServer server;
    MemoryService *memory;
    Logger logger;
    uint16_t startedAt;
    void handleRoot();
    void handleSetup();
    void handleRestart();
    WebServer &setMemory(MemoryService &memory);
    void create();
    void restartDeviceAfter5Min();

public:
    WebServer();
    WebServer(MemoryService &memory);
    void loop();
};

#endif