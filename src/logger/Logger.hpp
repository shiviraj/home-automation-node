#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>
#include <Arduino.h>

using namespace std;

void begin(int baudrate)
{
    Serial.begin(baudrate);
};

void info(string message)
{
    Serial.println("{ \"label\": \"INFO\", \"message\":\"" + String(message.c_str()) + "\"}");
}

void error(string message)
{
    Serial.println("{ \"label\": \"ERROR\", \"errorMessage\":\"" + String(message.c_str()) + "\"}");
}

#endif