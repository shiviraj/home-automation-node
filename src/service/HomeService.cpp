#include <service/HomeService.hpp>

HomeService::HomeService()
{
    this->mqttService = NULL;
    this->node = "";
}

HomeService::HomeService(MQTTService &mqttService, PinService &pinService, String node)
{
    setMQTTService(mqttService);
    setPinService(pinService);
    this->node = node;
}

HomeService &HomeService::setMQTTService(MQTTService &mqttService)
{
    this->mqttService = &mqttService;
    return *this;
}

HomeService &HomeService::setPinService(PinService &pinService)
{
    this->pinService = &pinService;
    return *this;
}

HomeService &HomeService::init(String topics[], unsigned int length)
{
    mqttService->init(this->callback());
    bool result = mqttService->connect(this->node);
    logger.info(result ? "MQTT Connected" : "MQTT not Connected");
    mqttService->subscribe(node, topics, length);
    delay(2000);
    mqttService->publish(node + "/devices");
    return *this;
}

void HomeService::loop()
{
    mqttService->loop(this->node);
}

MQTTCallback HomeService::callback()
{
    return [&](char *topicName, uint8_t *payload, unsigned int length)
    {
        String topic = String(topicName).substring(this->node.length() + 1);

        String message = "";
        for (unsigned int i = 0; i < length; i++)
        {
            message += char(payload[i]);
        }
        logger.info("Recieved topic " + topic);

        if (topic.equals("devices"))
        {
            pinService->addDevices(message);
        }
    };
}