#include <service/ConfigManager.hpp>

ConfigManager::ConfigManager() {}

ConfigManager::ConfigManager(MemoryService &memory)
{
    setMemory(memory);
}

ConfigManager &ConfigManager::setMemory(MemoryService &memory)
{
    this->memory = &memory;
    return *this;
}

String ConfigManager::getSSID()
{
    return this->memory->ssid;
}

String ConfigManager::getPassword()
{
    return this->memory->password;
}

String ConfigManager::getHost()
{
    return this->memory->host;
}

String ConfigManager::getUsername()
{
    return this->memory->username;
}

String ConfigManager::getPass()
{
    return this->memory->pass;
}