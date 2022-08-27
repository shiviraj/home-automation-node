#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <HardwareSerial.h>

class Logger
{
private:
    int baudrate;
    void begin();

public:
    Logger();
    Logger(int baudrate);
    void info(String message);
    void error(String message);
};

#endif