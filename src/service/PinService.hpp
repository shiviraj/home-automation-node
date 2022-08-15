#ifndef PIN_SERVICE_HPP
#define PIN_SERVICE_HPP

#include <Arduino.h>
#include <list>
#include <iterator>
#include <domain/Pin.hpp>

using namespace std;

class PinService
{
private:
    list<Pin> pins;
    char *RESTART = "RESTART";

public:
    PinService() {}

    PinService(list<Pin> pins)
    {
        (*this).pins = pins;
    }

    int set_pinmode()
    {
        list<Pin>::iterator it;
        for (it = pins.begin(); it != pins.end(); ++it)
        {
            Pin pin = *it;
            int type = pin.type == "INPUT" ? INPUT : OUTPUT;
            pinMode(pin.no, type);
            delay(100);
        }
        return pins.size();
    }

    void restart()
    {
        write(RESTART, HIGH);
    }

private:
    Pin find(char *name)
    {
        list<Pin>::iterator it;
        for (it = pins.begin(); it != pins.end(); ++it)
        {
            Pin pin = *it;
            if (pin.name == name)
            {
                return pin;
            }
        }
        return Pin();
    }

    int read(char *name)
    {
        Pin pin = find(name);
        auto readPin = pin.is_digital ? digitalRead : analogRead;
        return readPin(pin.no);
    }

    void write(char *name, int value)
    {
        Pin pin = find(name);
        if (pin.is_digital)
            return digitalWrite(pin.no, value);
        analogWrite(pin.no, value);
    }
};

#endif