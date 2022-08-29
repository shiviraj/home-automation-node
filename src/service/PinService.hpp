#ifndef PIN_SERVICE_HPP
#define PIN_SERVICE_HPP

#include <list>
#include <iterator>
#include <Arduino.h>
#include <logger/Logger.hpp>
#include <service/MQTTService.hpp>

using namespace std;

class PinService
{
private:
    list<String> devices;
    Logger logger;

public:
    PinService();
    void addDevices(String devices);
    void updateState(String device);
    void updateState(MQTTService &mqttService);

private:
    void setPinMode(String device);
    void write(String device);
    int read(String device);
    String getId(String device);
    int getMode(String device);
    int getType(String device);
    int getPin(String device);
    int getValue(String device);
    String getValueString(String device);
    String updateValue(String device, int value);
};

#endif