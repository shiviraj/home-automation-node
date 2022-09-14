#include <service/MemoryService.hpp>

MemoryService::MemoryService()
{
    EEPROM.begin(512);
    String vars[5];
    for (int i = 0; i < variables; i++)
    {
        for (int memory = i * memorySize; memory < (i + 1) * memorySize; memory++)
        {
            char ch = char(EEPROM.read(memory));
            if (ch != char(0))
                vars[i] += ch;
        }
        logger.info(vars[i]);
    }
    this->ssid = vars[0];
    this->password = vars[1];
    this->host = vars[2];
    this->username = vars[3];
    this->pass = vars[4];
}

void MemoryService::setVars(String ssid, String password, String host, String username, String pass)
{
    for (int i = 0; i < memorySize * variables; ++i)
    {
        EEPROM.write(i, 0);
    }
    EEPROM.commit();

    logger.info("SSID: " + ssid);
    logger.info("Password: " + password);
    logger.info("Host: " + host);
    logger.info("Username: " + username);
    logger.info("Pass: ******");
    String vars[] = {ssid, password, host, username, pass};

    for (int count = 0; count < variables; count++)
    {
        String value = vars[count];
        logger.info(value);
        for (unsigned int i = 0; i < value.length(); i++)
        {
            EEPROM.write(count * memorySize + i, value[i]);
        }
    }
    EEPROM.commit();
}