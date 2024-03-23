#include <iostream>
#include "Str.h"

using namespace OurString;

int Str::lenLocal(const char* string) const {
    int length = 0;

    for (int i = 0; string[i] != '\0'; ++i) {
        length++;
    }
    return length;
}

Str::Str() {
    ptr = nullptr;
}

Str::Str(const char* string) {
    int length = lenLocal(string);
    ptr = new char[sizeof(char) * length + 1];

    for (int i = 0; i <= length; ++i) { // <= to include '\0'
        ptr[i] = string[i];
    }
}

Str::Str(const Str& obj) {
    int length = lenLocal(obj.ptr);
    ptr = new char[sizeof(char) * length + 1];

    for (int i = 0; i <= length; ++i) { // <= to include '\0'
        ptr[i] = obj.ptr[i];
    }
}

int Str::len() const {
    return lenLocal(ptr);
}

Str::~Str() {
    delete[] ptr; // To delete the whole array of char, "delete ptr" will delete the first location in the array;
}

Str::operator const char* () const {
    return ptr;
}

void Str::operator= (const Str& obj) {
    if (this == &obj) return; // To avoid self assignment

    delete[] ptr; // To prevent memory leaks

    int length = lenLocal(obj.ptr);
    ptr = new char[sizeof(char) * length + 1];

    for (int i = 0; i <= length; ++i) { // <= to include '\0'
        ptr[i] = obj.ptr[i];
    }
}

void Str::operator= (const char* string) {
    delete[] ptr; // To prevent memory leaks

    int length = lenLocal(string);
    ptr = new char[sizeof(char) * length + 1];

    for (int i = 0; i <= length; ++i) { // <= to include '\0'
        ptr[i] = string[i];
    }
}

Str Str::operator+ (const Str& obj) const {
    int length1 = lenLocal(this->ptr);
    int length2 = lenLocal(obj.ptr);

    Str result;
    result.ptr = new char[sizeof(char) * (length1 + length2) + 1];

    for (int i = 0; i < length1; ++i) {
        result.ptr[i] = this->ptr[i];
    }

    for (int i = 0; i <= length2; ++i) {
        result.ptr[length1 + i] = obj.ptr[i];
    }

    return result;
}

void Str::operator+= (const Str& obj) {
    int length1 = lenLocal(this->ptr);
    int length2 = lenLocal(obj.ptr);

    Str result;
    result.ptr = new char[sizeof(char) * (length1 + length2) + 1];

    for (int i = 0; i < length1; ++i) {
        result.ptr[i] = this->ptr[i];
    }

    for (int i = 0; i <= length2; ++i) {
        result.ptr[length1 + i] = obj.ptr[i];
    }

    *this = result;
}

bool Str::operator== (const Str& obj) const {
    if (lenLocal(obj.ptr) != lenLocal(this->ptr)) {
        return false;
    }

    for (int i = 0; obj.ptr[i] != '\0'; i++) {
        if (obj.ptr[i] != this->ptr[i])
            return false;
    }

    return true;
}

std::istream& OurString::operator>>(std::istream& is, Str& obj) {
    char temp[1024];

    is >> temp; // Store in temp
    obj = temp; // Put temp in obj
    return is; // Return the input stream to allow chaining of input operations
}