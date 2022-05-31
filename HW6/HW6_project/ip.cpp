#include "ip.h"
#include <stdio.h>
#include <iostream>
#include <stddef.h>
#include "string.h"
#include <cstring>
#include "field.h"

#define BITS_NUM 32

Ip::Ip(String pattern) : Field(pattern), start_ip(0), end_ip(0) {  }

Ip::~Ip() { }

bool Ip::match_value(String value) const{
    String* ip_fields;
    size_t ip_fields_num;
    value.split(".", &ip_fields, &ip_fields_num);
    if(ip_fields_num != 4) {
        delete[] ip_fields;
        return false;
    }
    int ip = (ip_fields[0].to_integer()<<24) | (ip_fields[1].to_integer()<<16) |  (ip_fields[2].to_integer()<<8) | (ip_fields[3].to_integer());
    delete[] ip_fields;
    if((ip >= start_ip) && (ip <= end_ip)) return true;
    else return false;
}

bool Ip::set_value(String val) {
    String* val_fields;
    size_t fields_num;
    val.split("/", &val_fields, &fields_num);
    if(fields_num != 2) {
        delete[] val_fields;
        return false;
    }
    int mask = val_fields[1].to_integer();
    String* ip_fields;
    size_t ip_fields_num;
    val.split(".", &ip_fields, &ip_fields_num);
    if(ip_fields_num != 4) {
        delete[] ip_fields;
        delete[] val_fields;
        return false;
    }
    int ip = (ip_fields[0].to_integer()<<24) | (ip_fields[1].to_integer()<<16) |  (ip_fields[2].to_integer()<<8) | (ip_fields[3].to_integer());
    int start_bin_mask = 0xFFFFFFFF<<(BITS_NUM-mask);
    int end_bin_mask = 0xFFFFFFFF>>(mask);
    this->start_ip = ip & start_bin_mask;
    this->end_ip = ip | end_bin_mask;
    delete[] val_fields;
    delete[] ip_fields;
    return true;
}



