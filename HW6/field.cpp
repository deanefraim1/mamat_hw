#include "string.h"
#include "field.h"


Field::Field(String pattern) : pattern(pattern) { }

Field::~Field() { }

bool Field::match(String packet) {
    String* packet_fields;
    size_t fields_num;
    packet.trim().split(",", &packet_fields, &fields_num);
    for(size_t i = 0; i<fields_num; i++) {
        String* curr_field;
        size_t num;
        packet_fields[i].trim().split("=", &curr_field, &num);
        String curr_field_type = curr_field[0].trim();
        String curr_field_value = curr_field[1].trim();
        delete[] curr_field;
        if(curr_field_type.equals(this->pattern)
           && this->match_value(curr_field_value)) {
            delete[] packet_fields;
            return true;
        }
    }
    if(fields_num != 0) {
        delete[] packet_fields;
    }
    return false;
}
