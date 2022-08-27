#ifndef WIFI_SERVICE_HPP
#define WIFI_SERVICE_HPP

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>
#include <logger/Logger.hpp>

Logger logger;

void wifiInit(String node)
{
    WiFiManager wifiManager;
    wifiManager.autoConnect(node.c_str());
    logger.info((char *)"connected...");
}

#endif