#ifndef WIFI_SERVICE_HPP
#define WIFI_SERVICE_HPP

#include <iostream>
#include <string>

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <logger/Logger.hpp>

void wifiInit(std::string node)
{
    WiFiManager wifiManager;
    wifiManager.autoConnect(node.c_str());
    info((char *)"connected...");
}

#endif