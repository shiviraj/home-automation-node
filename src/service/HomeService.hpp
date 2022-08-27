#ifndef HOME_SERVICE_HPP
#define HOME_SERVICE_HPP

#include <service/MQTTService.hpp>
#include <service/PinService.hpp>

class HomeService
{
private:
    MQTTService *mqttService;
    PinService *pinService;
    String node;
    Logger logger;
    MQTTCallback callback();

public:
    HomeService();
    HomeService(MQTTService &mqttService, PinService &pinService, String node);

    HomeService &setMQTTService(MQTTService &mqttService);
    HomeService &setPinService(PinService &pinService);
    MQTTService &setClient(PubSubClient &client);

    HomeService &init(String topics[], unsigned int length);

    void loop();
};

#endif