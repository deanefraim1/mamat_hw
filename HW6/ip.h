#ifndef IP_H
#define IP_H

#include <stdio.h>
#include "field.h"

class Ip : public Field {
private:
    unsigned int start_ip, end_ip;
    bool match_value(String value) const;
public:
    Ip(String pattern);
    ~Ip();
    bool set_value(String val);
};
#endif
