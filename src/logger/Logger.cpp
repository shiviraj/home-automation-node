#include <logger/Logger.hpp>

Logger::Logger()
{
    this->baudrate = 115200;
    begin();
}

Logger::Logger(int baudrate)
{
    this->baudrate = baudrate;
    begin();
}

void Logger::begin()
{
    Serial.begin(baudrate);
};

void Logger::info(String message)
{
    Serial.println("{ \"label\": \"INFO\", \"message\":\"" + message + "\"}");
}

void Logger::infoF(String message)
{
    Serial.printf("{ \"label\": \"INFO\", \"message\":\"%s\"}\r", message.c_str());
}

void Logger::error(String message)
{
    Serial.println("{ \"label\": \"ERROR\", \"errorMessage\":\"" + message + "\"}");
}