#include <service/PinService.hpp>

PinService::PinService() {}

void PinService::addDevices(String allDevices)
{
    this->devices.clear();
    int startIndex = 0;
    int endIndex = 0;
    while (endIndex != -1)
    {
        endIndex = allDevices.indexOf("\n");
        String device = allDevices.substring(startIndex, endIndex);
        this->devices.push_back(device);
        setPinMode(device);
        allDevices = allDevices.substring(endIndex + 1);
    }
    logger.info("Succefully added devices, count: " + String(this->devices.size()));
}

void PinService::updateState(String updatedDevice)
{
    list<String>::iterator it;
    String updatedDeviceId = getId(updatedDevice);
    for (it = devices.begin(); it != devices.end(); ++it)
    {
        if (getId(*it).equals(updatedDeviceId))
        {
            *it = updateValue(*it, getValue(updatedDevice));
            return write(*it);
        }
    }
}

void PinService::setPinMode(String device)
{
    int pin = this->getPin(device);
    int mode = this->getMode(device);
    pinMode(pin, mode);
    delay(10);
    write(device);
    logger.info("Setting mode at pin: " + String(pin) + " mode: " + (mode ? "OUTPUT" : "INPUT"));
}

void PinService::write(String device)
{
    if (this->getMode(device))
    {
        int pin = this->getPin(device);
        int value = this->getValue(device);
        logger.info("writing value at pin: " + String(pin) + " value: " + String(value));
        if (this->getType(device))
            return digitalWrite(pin, value);
        analogWrite(pin, value);
    }
}

int PinService::read(String device)
{
    if (!getMode(device))
    {
        int pin = getPin(device);
        if (getType(device))
            return digitalRead(pin);
        return analogRead(pin);
    }
    return 0;
}

String PinService::getId(String device)
{
    return device.substring(0, 8);
}

int PinService::getMode(String device)
{
    return device.substring(9, 10).toInt();
}

int PinService::getType(String device)
{
    return device.substring(11, 12).toInt();
}

int PinService::getPin(String device)
{
    return device.substring(15, 17).toInt();
}

int PinService::getValue(String device)
{
    return getValueString(device).toInt();
}

String PinService::getValueString(String device)
{
    return device.substring(18);
}

String PinService::updateValue(String device, int value)
{
    int lastIndex = device.lastIndexOf("/");
    String deviceWithoutValue = device.substring(0, lastIndex + 1);
    return deviceWithoutValue + value;
}

void PinService::updateState(MQTTService &mqttService)
{
    list<String>::iterator it;
    for (it = devices.begin(); it != devices.end(); ++it)
    {
        if (!getMode(*it))
        {
            int value = read(*it);
            if (value != getValue(*it))
            {
                *it = updateValue(*it, value);
                mqttService.publish("update-state", *it);
            }
        }
    }
}
