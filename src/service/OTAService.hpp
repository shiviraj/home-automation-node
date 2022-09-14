#ifndef OTA_SERVICE_HPP
#define OTA_SERVICE_HPP

#include <ArduinoOTA.h>
#include <logger/Logger.hpp>

using namespace std;

class OTAService
{

private:
    Logger logger;
    bool readyFlag = false;

public:
    OTAService();
    void setup();
    void setUpdateMode();
    void enable();
};

#endif