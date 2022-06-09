#ifndef PORT_H
#define PORT_H

#include <stdio.h>
#include "field.h"

class Port : public Field {
private:
    int start_port, end_port;
    bool match_value(String value) const;
public:
    Port(String pattern);
    ~Port();
    bool set_value(String val);
};

#endif
