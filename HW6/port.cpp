#include "string.h"
#include "field.h"
#include "port.h"

Port::Port(String pattern) : Field(pattern), start_port(0), end_port(0) {  }

Port::~Port() { }

bool Port::match_value(String value) const{
    int port = value.trim().to_integer();
    if((port >= this->start_port) && (port <= this->end_port)) return true;
    else return false;
}

bool Port::set_value(String val) {
    String* port_fields;
    size_t port_fields_num;
    val.trim().split("-", &port_fields, &port_fields_num);
    if(port_fields_num != 2) {
        delete[] port_fields;
        return false;
    }
    this->start_port = port_fields[0].trim().to_integer();
    this->end_port = port_fields[1].trim().to_integer();
    delete[] port_fields;
    return true;
}



