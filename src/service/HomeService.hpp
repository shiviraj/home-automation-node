#ifndef HOME_SERVICE_HPP
#define HOME_SERVICE_HPP

#include <service/MQTTService.hpp>
#include <service/PinService.hpp>
#include <service/OTAService.hpp>

class HomeService
{
private:
    MQTTService *mqttService;
    PinService *pinService;
    OTAService *otaService;
    String node;
    Logger logger;
    MQTTCallback callback();

public:
    HomeService();
    HomeService(MQTTService &mqttService, PinService &pinService, OTAService &otaService, String node);

    HomeService &setMQTTService(MQTTService &mqttService);
    HomeService &setPinService(PinService &pinService);
    HomeService &setClient(PubSubClient &client);
    HomeService &setOTAService(OTAService &otaService);

    HomeService &init();

    void loop();
};

#endif