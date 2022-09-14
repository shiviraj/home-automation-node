#include <service/MQTTService.hpp>

MQTTService::MQTTService()
{
    this->client = NULL;
    this->host = "";
    this->port = 0;
    this->username = "";
    this->password = "";
}

MQTTService::MQTTService(String node, PubSubClient &client, String host, int port, String username, String password)
{
    setClient(client);
    this->node = node;
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
    if (!connected())
    {
        logger.info("connecting with MQTT...");
        delay(10000);
        bool status = client->connect(id.c_str(), username.c_str(), password.c_str());
        logger.info(status ? "Successfully connected with MQTT" : "Failed to connect with MQTT");
    }
    return connected();
}

void MQTTService::loop(String id)
{
    client->loop();
}

bool MQTTService::connected()
{
    return client->connected();
}

bool MQTTService::publish(String topic)
{
    return publish(topic, "");
}

bool MQTTService::publish(String topicName, String message)
{
    String topic = node + "/" + topicName;
    logger.info("Published topic: " + topic + " message: " + message);
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