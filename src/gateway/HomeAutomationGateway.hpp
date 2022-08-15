#ifndef HOME_AUTOMATION_GATEWAY_HPP
#define HOME_AUTOMATION_GATEWAY_HPP

#include <utils/WebClient.hpp>

class HomeAutomationGateway
{
private:
    std::string node;
    WebClient client;

public:
    HomeAutomationGateway() {}

    HomeAutomationGateway(std::string node)
    {
        (*this).node = node;
    }

    WebResponse getPinMapping()
    {
        return client.get("", "");
    }
};

#endif
