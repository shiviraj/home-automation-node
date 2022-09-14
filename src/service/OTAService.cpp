

#include <service/OTAService.hpp>

OTAService::OTAService() {}

void OTAService::enable()
{
    if (!this->readyFlag)
    {
        setup();
        this->readyFlag = true;
    }

    uint16_t timeElapsed = 0, timeStart = millis();
    while (timeElapsed < 30000)
    {
        ArduinoOTA.handle();
        timeElapsed = millis() - timeStart;
        delay(10);
    }
}

void OTAService::setup()
{
    ArduinoOTA.onStart([]()
                       {
                        Logger logger;
                        String type = ArduinoOTA.getCommand() == U_FLASH ? "sketch" : "filesystem";
                        logger.info("Start updating " + type); });

    ArduinoOTA.onEnd([]()
                     {
                        Logger logger;
                        logger.info("Successfully uploaded");
                        ESP.restart(); });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                          {
                              Logger logger;
                              logger.infoF("Progress: "+ String(progress / (total / 100))+"%"); });

    ArduinoOTA.onError([](ota_error_t error)
                       {
                        Logger logger;
                           if (error == OTA_AUTH_ERROR)
                           {
                               logger.info("Error: Auth Failed");
                           }
                           else if (error == OTA_BEGIN_ERROR)
                           {
                               logger.info("Error: Begin Failed");
                           }
                           else if (error == OTA_CONNECT_ERROR)
                           {
                               logger.info("Error: Connect Failed");
                           }
                           else if (error == OTA_RECEIVE_ERROR)
                           {
                               logger.info("Error: Receive Failed");
                           }
                           else if (error == OTA_END_ERROR)
                           {
                               logger.info("Error: End Failed");
                           } });
    ArduinoOTA.begin();
}