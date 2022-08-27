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
    logger.info("Succefully added devices count: " + String(this->devices.size()));
}

// // void PinService::updateValue(Device updatedDevice)
// // {
// //     Device device = *findDevice(updatedDevice.id);
// //     device.updateValue(updatedDevice.value);
// //     write(device);
// // }

void PinService::setPinMode(String device)
{
    int pin = this->getPin(device);
    int mode = this->getMode(device);
    pinMode(pin, mode);
    delay(10);
    write(device);
    logger.info("Set pinmode of pin " + String(pin) + " mode " + (mode ? "OUTPUT" : "INPUT"));
}

// String PinService::findIndexById(String id)
// {
//     for (unsigned int i = 0; i < this->devices.size(); i++)
//     {
//         if (this->devices[i].startsWith(id))
//         {
//             return i;
//         }
//     }
//     return -1;
// };

void PinService::write(String device)
{
    if (this->getMode(device))
    {
        int pin = this->getPin(device);
        int value = this->getValue(device);
        if (this->getType(device))
            return digitalWrite(pin, value);
        analogWrite(pin, value);
        logger.info("write value to pin: " + String(pin) + " value: " + String(value));
    }
}

// int PinService::read(String device)
// {
//     if (!getMode(device))
//     {
//         int pin = getPin(device);
//         logger.info("reading value of pin: " + String(pin));
//         if (getType(device))
//             return digitalRead(pin);
//         return analogRead(pin);
//     }
//     return 0;
// }

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

int PinService::getNumber(String device)
{
    return device.substring(13, 14).toInt();
}

int PinService::getPin(String device)
{
    return device.substring(15, 17).toInt();
}

int PinService::getValue(String device)
{
    return device.substring(18).toInt();
}
