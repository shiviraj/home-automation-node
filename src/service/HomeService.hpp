#ifndef HOME_SERVICE_HPP
#define HOME_SERVICE_HPP

#include <gateway/HomeAutomationGateway.hpp>
#include <ws/WebSocket.hpp>
#include <utils/WebResponse.hpp>

class HomeService
{
private:
    HomeAutomationGateway homeAutomationGateway;
    WebSocket websocket;

public:
    HomeService(std::string node)
    {
        (*this).homeAutomationGateway = HomeAutomationGateway(node);
        (*this).websocket = WebSocket(node);
    }

    void init()
    {
        WebResponse response = homeAutomationGateway.getPinMapping();
        if (response.error)
        {
            
        }
    }

    void loop() {}
};

#endif