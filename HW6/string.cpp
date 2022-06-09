#include <iostream>
#include <stddef.h>
#include "string.h"
#include <cstring>

String::String() : data(NULL), length(0) {
    this->data = new char[(this->length)+1];
    *(this->data) = '\0';
}
    
String::String(const String &str) : data(NULL), length(str.length) {
    this->data = new char[(this->length)+1];
    strcpy(this->data, str.data);
}

String::String(const char *str) {
    if(str != NULL) {
        this->length = strlen(str);
        this->data = new char[(this->length)+1];
        strcpy(this->data, str);
    }
    else {
        this->length = 0;
        this->data = new char[(this->length)+1];
        *(this->data) = '\0';
    }
}

String::~String() {
    delete[] this->data;
}

String& String::operator=(const String &rhs) {
    if(this == &rhs) return *this;
    this->length = rhs.length;
    delete[] this->data;
    this->data = new char[(this->length)+1];
    strcpy(this->data, rhs.data);
    return *this;
}

String& String::operator=(const char *str) {
    this->length = strlen(str);
    delete[] this->data;
    this->data = new char[(this->length)+1];
    strcpy(this->data, str);
    return *this;
}

bool String::equals(const String &rhs) const {
    if(this->length != rhs.length) return false;
    else if (strcmp(this->data, rhs.data) != 0) return false;
    else return true;
}

bool String::equals(const char *rhs) const {
    if (strcmp(this->data, rhs) != 0) return false;
    else return true;
}

void String::split(const char *delimiters,
                   String **output, size_t *size) const{
    String clone_string_1 = *this;
    char* curr_piece = strtok(clone_string_1.data, delimiters);
    int counter = 0;
    while(curr_piece != NULL) {
        counter++;
        curr_piece = strtok(NULL, delimiters);
    }
    *size = (size_t)counter;
    if(output == NULL) return;
    String clone_string_2 = *this;
    *output = new String[counter];
    curr_piece = strtok(clone_string_2.data, delimiters);
    for(int i = 0; i<counter; i++) {
        (*output)[i] = curr_piece;
        curr_piece = strtok(NULL, delimiters);
    }
}

int String::to_integer() const { return atoi(this->data); }

String String::trim() const {
    int size = (int)this->length;
    int start = 0, end = --size;
    while(((this->data)[start]) == ' ') start++;
    if(start == size) return String();
    while((this->data)[end] == ' ') end--;
    int trim_size = end-start+1;
    char* tmp_str = new char[trim_size+1];
    strncpy(tmp_str, (this->data)+start, trim_size);
    tmp_str[trim_size]='\0';
    String new_string = String(tmp_str);
    delete[] tmp_str;
    return new_string;
}
