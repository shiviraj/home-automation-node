#ifndef PIN_MAPPING_HPP
#define PIN_MAPPING_HPP

class Pin
{
public:
    char *name, *type;
    int no;
    bool is_digital = true;

    Pin() {}

    Pin(char *name, int no, char *type)
    {
        (*this).name = name;
        (*this).no = no;
        (*this).type = type;
    }

    Pin(char *name, int no, char *type, bool digital)
    {
        (*this).name = name;
        (*this).no = no;
        (*this).type = type;
        (*this).is_digital = digital;
    }
};

#endif
