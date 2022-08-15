#ifndef WEB_SOCKET_HPP
#define WEB_SOCKET_HPP

class WebSocket
{
private:
    std::string node;

public:
    WebSocket() {}

    WebSocket(std::string node)
    {
        (*this).node = node;
    }
};

#endif