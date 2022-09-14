#ifndef MQTT_SERVICE_HPP
#define MQTT_SERVICE_HPP

#include <PubSubClient.h>
#include <logger/Logger.hpp>

typedef std::function<void(char *, uint8_t *, unsigned int)> MQTTCallback;

class MQTTService
{
private:
    PubSubClient *client;
    String host, node;
    int port;
    String username;
    String password;
    Logger logger;

public:
    MQTTService();
    MQTTService(String node, PubSubClient &client, String host, int port, String username, String password);

    MQTTService &setClient(PubSubClient &client);

    MQTTService &init(MQTTCallback callback);

    void loop(String id);
    bool connect(String id);
    bool publish(String topic);
    bool publish(String topic, String message);
    bool connected();

    void subscribe(String node, String topics[], unsigned int length);
};

#endif