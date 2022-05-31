#include <iostream>
#include <stdio.h>
#include <stddef.h>
#include "string.h"
#include <cstring>
#include "ip.h"
#include "port.h"
#include "input.h"

extern int check_args(int, char**);
extern void parse_input(Field&);

int main(int argc, char* argv[]) {
    if(check_args(argc, argv) != 0 ) return 1;
    String* rule_fields;
    size_t rule_fields_num;
    String rule_string = argv[1];
    rule_string.split("= ,", &rule_fields, &rule_fields_num);
    if(rule_fields_num != 2) {
        delete[] rule_fields;
        return 1;
    }
    String pattern = rule_fields[0].trim();
    String rule = rule_fields[1].trim();
    delete[] rule_fields;
    if(pattern.equals("src-ip") || pattern.equals("dst-ip")) {
        Ip ip(pattern);
        ip.set_value(rule);
        parse_input(ip);
    }
    else if(pattern.equals("src-port") || pattern.equals("dst-port")) {
        Port port(pattern);
        port.set_value(rule);
        parse_input(port);
    }
    return 0;
}
