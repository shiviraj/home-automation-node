#include <service/WebServer.hpp>

using namespace std;

WebServer::WebServer()
{
    create();
}
WebServer::WebServer(MemoryService &memory)
{
    setMemory(memory);
    create();
    server.begin();
    logger.info("started server");
    this->startedAt = millis();
}

void WebServer::loop()
{
    server.handleClient();
    restartDeviceAfter5Min();
}

void WebServer::restartDeviceAfter5Min()
{
    if (millis() - this->startedAt > 300000)
    {
        logger.info("Restarting node, there is no intraction done in setup mode...");
        // delay(5000);
        ESP.restart();
    }
}

WebServer &WebServer::setMemory(MemoryService &memory)
{
    this->memory = &memory;
    return *this;
}

void WebServer::create()
{
    server.on("/", std::bind(&WebServer::handleRoot, this));
    server.on("/setup", std::bind(&WebServer::handleSetup, this));
    server.on("/restart", std::bind(&WebServer::handleRestart, this));
}

void WebServer::handleRoot()
{
    String content = "<html><h1>Home Automation</h1><form action='setup'>";
    content += "<label>SSID: </label><br/><input name='ssid' length=64 required value='" + memory->ssid + "'><br/><br/>";
    content += "<label>Password: </label><br/><input name='password' length=64 required value='" + memory->password + "'><br/><br/>";
    content += "<label>MQTT Host: </label><br/><input name='host' length=64 required value='" + memory->host + "'><br/><br/>";
    content += "<label>MQTT Username: </label><br/><input name='username' length=64 required value='" + memory->username + "'><br/><br/>";
    content += "<label>MQTT Password: </label><br/><input name='pass' length=64 required value='" + memory->pass + "'><br/><br/>";
    content += "<input type='submit'/></form><br/>";
    content += "<a href='/restart'><button>Restart Node</button></a></html>";

    server.setContentLength(content.length());
    server.send(200, "text/html", content);
}

void WebServer::handleSetup()
{
    String qssid = server.arg("ssid");
    String qpassword = server.arg("password");
    String qhost = server.arg("host");
    String qusername = server.arg("username");
    String qpass = server.arg("pass");

    if (qssid.length() > 0 && qpassword.length() > 0 && qhost.length() > 0 && qusername.length() > 0 && qpass.length() > 0)
    {
        memory->setVars(qssid, qpassword, qhost, qusername, qpass);
        server.send(200, "text/html", "<html><h2>Successfully updated!!</h2></html>");
        ESP.restart();
        return;
    }
    server.send(404, "text/html", "<h2 style='color:red'>404 Not Found</h2>");
}

void WebServer::handleRestart()
{
    server.send(200, "text/html", "<html><h2>Successfully restarted node!!</h2></html>");
    logger.info("Restarting...");
    delay(1000);
    ESP.restart();
}