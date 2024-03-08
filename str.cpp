#include <iostream>
#include "str.h"
using namespace std;
using namespace OurString;

int str::len_local(const char* String) const {
	int length = 0;

	for (int i = 0; String[i] != '\0'; ++i) {
		length++;
	}
	return length;
}

str::str(const char* String) {
	int length = len_local(String);
	ptr = new char[sizeof(char) * length + 1];

	for (int i = 0; i <= length; ++i) { // <= to include '\0'
		ptr[i] = String[i];
	}
}

str::str(const str& obj) {
	int length = len_local(obj.ptr);
	ptr = new char[sizeof(char) * length + 1];

	for (int i = 0; i <= length; ++i) { // <= to include '\0'
		ptr[i] = obj.ptr[i];
	}
}

int str::len() const {
	return len_local(ptr);
}

str::~str() {
	delete[] ptr; //to delete the whole array of char, "delete ptr" will delete the first location in the array;
}

str::operator const char* () const {
	return ptr;
}

void str::operator = (str obj) {

	delete[] ptr; // to prevent memory leaks, if we left that, the old

	int length = len_local(obj.ptr);
	ptr = new char[sizeof(char) * length + 1];

	for (int i = 0; i <= length; ++i) { // <= to include '\0'
		ptr[i] = obj.ptr[i];
	}
}

bool str::operator == (str obj) {
	if (len_local(obj.ptr) != len_local(this->ptr)) {
		return false;
	}

	for (int i = 0; *(obj.ptr + i) != '\0'; i++) {
		if (*(obj.ptr + i) != *(this->ptr + i))
			return false;
	}

	return true;
}