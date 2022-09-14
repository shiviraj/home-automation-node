#include <service/ConfigManager.hpp>
#include <service/WebServer.hpp>
#include <service/WifiService.hpp>
#include <service/HomeService.hpp>
#include <service/MQTTService.hpp>
#include <service/PinService.hpp>
#include <service/OTAService.hpp>

void setup()
{
    const String node = "node-1";
    String topics[] = {"devices", "update-state", "ota-update", "restart"};
    const int topicsLength = 4;
    const int mqttPort = 1883;

    MemoryService memory;
    ConfigManager configManager(memory);
    WiFiService wifiService(configManager);

    const String mqttHost = configManager.getHost();
    const String mqttUsername = configManager.getUsername();
    const String mqttPassword = configManager.getPass();

    wifiService.autoConnect();

    WiFiClient wifiClient;
    PubSubClient client(wifiClient);
    MQTTService mqttService(node, client, mqttHost, mqttPort, mqttUsername, mqttPassword);
    PinService pinService;
    OTAService otaService;

    HomeService homeService(mqttService, pinService, otaService, node);
    homeService.init();
    mqttService.connect(node);

    if (!wifiService.connected() || !mqttService.connected())
    {
        wifiService.setupAP(node);
        WebServer server(memory);
        while (true)
        {
            server.loop();
            delay(100);
        }
    }

    mqttService.subscribe(node, topics, topicsLength);
    mqttService.publish("devices");

    while (true)
    {
        uint16_t startedAt = millis();
        while (!wifiService.connected() || !mqttService.connected())
        {
            if (millis() - startedAt > 60000)
                pinService.restart();
            wifiService.autoConnect();
            mqttService.connect(node);
        }

        homeService.loop();
        delay(10);
    }
}

void loop() {}
