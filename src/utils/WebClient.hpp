#ifndef WEBCLIENT_HPP
#define WEBCLIENT_HPP

#include <iostream>
#include <string>

#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiClient.h>
#include <utils/WebResponse.hpp>
#include <utils/utils.hpp>
#include <logger/Logger.hpp>

using namespace std;

HTTPClient http;

class WebClient
{
private:
public:
    WebClient() {}

    WebResponse get(string base_url)
    {
        return get(base_url, "");
    }

    WebResponse get(string base_url, string path)
    {
        string url = base_url + path;
        info("http get request " + url);

        WiFiClient client;
        http.begin(client, convertToString(url));

        WebResponse response = getResponse();
        http.end();
        return response;
    }

private:
    WebResponse getResponse()
    {
        int httpCode = http.GET();
        string statusCode = "status code: " + httpCode;
        if (httpCode == HTTP_CODE_OK)
        {
            string payload = convertTostring(http.getString());
            string logMessage = statusCode + " response: " + payload;
            info(logMessage);
            return WebResponse(payload);
        }
        info(statusCode);
        return WebResponse(true, statusCode);
    }
};

#endif