#include <iostream>
#include <string>

#include <service/WifiService.hpp>
#include <logger/Logger.hpp>
#include <service/HomeService.hpp>

using namespace std;

void setup()
{
    int baudrate = 115200;
    begin(baudrate);
    string node = "node-1";
    wifiInit(node);

    HomeService homeService = HomeService(node);

    homeService.init();

    while (true)
    {
        homeService.loop();
    }
}

void loop() {}
