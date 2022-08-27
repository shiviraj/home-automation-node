#include <service/WifiService.hpp>
#include <service/HomeService.hpp>
#include <service/MQTTService.hpp>
#include <service/PinService.hpp>

void setup()
{
    const String node = "node-1";
    const String mqttHost = "192.168.10.101";
    const int mqttPort = 1883;
    const String mqttUsername = "home-automation";
    const String mqttPassword = "Shiviraj";
    String topics[] = {"devices"};
    const int topicsLength = 1;

    wifiInit(node);

    WiFiClient wifiClient;
    PubSubClient client(wifiClient);

    MQTTService mqttService(client, mqttHost, mqttPort, mqttUsername, mqttPassword);
    PinService pinService;

    HomeService homeService(mqttService, pinService, node);

    homeService.init(topics, topicsLength);

    while (true)
    {
        homeService.loop();
        delay(1000);
    }
}

void loop() {}
