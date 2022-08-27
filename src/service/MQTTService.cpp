#include <service/MQTTService.hpp>

MQTTService::MQTTService()
{
    this->client = NULL;
    this->host = "";
    this->port = 0;
    this->username = "";
    this->password = "";
}

MQTTService::MQTTService(PubSubClient &client, String host, int port, String username, String password)
{
    setClient(client);
    this->host = host;
    this->port = port;
    this->username = username;
    this->password = password;
}

MQTTService &MQTTService::setClient(PubSubClient &client)
{
    this->client = &client;
    return *this;
}

MQTTService &MQTTService::init(MQTTCallback callback)
{
    client->setServer(host.c_str(), port);
    client->setCallback(callback);
    return *this;
}

bool MQTTService::connect(String id)
{
    logger.info("connecting with MQTT...");
    return client->connect(id.c_str(), username.c_str(), password.c_str());
}

void MQTTService::loop(String id)
{
    while (!client->connected())
    {
        delay(1000);
        connect(id);
    }
    client->loop();
}

bool MQTTService::publish(String topic)
{
    return publish(topic, "");
}

bool MQTTService::publish(String topic, String message)
{
    logger.info("Published topic " + topic);
    return client->publish(topic.c_str(), message.c_str());
}

void MQTTService::subscribe(String node, String topics[], unsigned int length)
{
    for (unsigned int i = 0; i < length; i++)
    {
        String topic = String(node + "_" + topics[i]);
        logger.info("Subscribed topic " + topic);
        client->subscribe(topic.c_str(), 1);
    }
}