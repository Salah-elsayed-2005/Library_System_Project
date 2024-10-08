#include <iostream>
#include "str.h"
#include <string>

using namespace std;

int str::len_local(const char* String) const {
    int length = 0;

    if(String != NULL)
        for (int i = 0; String[i] != '\0'; ++i) {
            length++;
        }

    return length;
}

str::str() {
    ptr = nullptr;
}

str::str(const char* String) {
    int length = len_local(String);
    ptr = new char[sizeof(char) * length + 1];

    if (String != NULL)
        for (int i = 0; i <= length; ++i) { // <= to include '\0'
            ptr[i] = String[i];
        }
    else
        ptr[0] = '\0';
}

str::str(const str& obj) {
    int length = len_local(obj.ptr);
    ptr = new char[sizeof(char) * length + 1];

    for (int i = 0; i <= length; ++i) { // <= to include '\0'
        ptr[i] = obj.ptr[i];
    }
}

str::str(const string& String) {
    int length = String.size();
    ptr = new char[sizeof(char) * length + 1];

    for (int i = 0; i <= length; ++i) { // <= to include '\0'
        ptr[i] = String[i];
    }
}

int str::len() const {
    return len_local(ptr);
}

string str::str2string() const {
    return string(ptr);
}

str::~str() {
    delete[] ptr; //to delete the whole array of char, "delete ptr" will delete the first location in the array;
}

str::operator const char* () const {
    return ptr;
}

void str::operator = (const str& obj) {
    if (this == &obj) return; //to avoid self assignment

    delete[] ptr; // to prevent memory leaks, if we left that, the old

    int length = len_local(obj.ptr);
    ptr = new char[sizeof(char) * length + 1];

    for (int i = 0; i <= length; ++i) { // <= to include '\0'
        ptr[i] = obj.ptr[i];
    }
}

void str::operator = (const char* String) {

    delete[] ptr; // to prevent memory leaks, if we left that, the old

    int length = len_local(String);
    ptr = new char[sizeof(char) * length + 1];

    for (int i = 0; i <= length; ++i) { // <= to include '\0'
        ptr[i] = String[i];
    }
}

void str::operator = (const string& String) {

    delete[] ptr; // to prevent memory leaks, if we left that, the old

    int length = String.size();
    ptr = new char[sizeof(char) * length + 1];

    for (int i = 0; i <= length; ++i) { // <= to include '\0'
        ptr[i] = String[i];
    }
}

str str::operator + (const str& obj) const {

    int length1 = len_local(this->ptr);
    int length2 = len_local(obj.ptr);

    str result;
    result.ptr = new char[sizeof(char) * (length1 + length2) + 1];



    for (int i = 0; i < length1; ++i) {
        result.ptr[i] = this->ptr[i];
    }

    for (int i = 0; i <= length2; ++i) {
        result.ptr[length1 + i] = obj.ptr[i];
    }

    return result;
}

str str::operator + (const char* string) const {
    str temp = str(string);

    return *this + temp;
}

str str::operator + (const string& String) const {

    str result = str(String);

    return *this + result;
}

str str::operator + (const int& num) const {

    str result = to_string(num).c_str();

    result += ptr;
    return result;
}

void str::operator += (const str& obj) {

    int length1 = len_local(this->ptr);
    int length2 = len_local(obj.ptr);

    str result;
    result.ptr = new char[sizeof(char) * (length1 + length2) + 1];



    for (int i = 0; i < length1; ++i) {
        result.ptr[i] = this->ptr[i];
    }

    for (int i = 0; i <= length2; ++i) {
        result.ptr[length1 + i] = obj.ptr[i];
    }

    *this = result;
}

void str::operator += (const string& String) {

    str result = str(String);

    *this = *this + String;
}

void str::operator += (const int& num) {
    str result = str();

    result = result + num;

    *this = *this + result;
}

bool str::operator == (const str& obj) const {
    if (len_local(obj.ptr) != len_local(this->ptr)) {
        return false;
    }

    for (int i = 0; *(obj.ptr + i) != '\0'; i++) {
        if (*(obj.ptr + i) != *(this->ptr + i))
            return false;
    }

    return true;
}

void str::operator += (const char* String) {

    str result = str(String);

    *this = *this + String;
}

std::istream& operator>>(std::istream& is, str& obj){
    char temp[1024];

    is >> temp; //store in temp
    obj = temp; // put temp in obj, why not "is >> obj.ptr" because we do not know the length of the entered data and storing that in obj.ptr, can write the data in places byond the places we have access to. and that will cause problems
    return is; // Return the input stream to allow chaining of input operations
}