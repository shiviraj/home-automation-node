#ifndef WEB_RESPONSE_HPP
#define WEB_RESPONSE_HPP

#include <iostream>
#include <string>

using namespace std;

class WebResponse
{
public:
    bool error = false;
    string error_message;
    string payload;

    WebResponse() {}

    WebResponse(bool is_error, string err_message)
    {
        error = is_error;
        error_message = err_message;
    }

    WebResponse(string response)
    {
        payload = response;
    }
};

#endif