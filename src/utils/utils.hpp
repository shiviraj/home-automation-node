#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <Arduino.h>

using namespace std;

string convertTostring(String text)
{
    return string(text.c_str());
}

String convertToString(string text)
{
    return String(text.c_str());
}

#endif