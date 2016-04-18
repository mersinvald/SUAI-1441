#include "string.hpp"
#include <cstring>

namespace msvd {

String::String() : len(0) {}

String::String(const String& b) {
    ptr = b.ptr;
    len = b.len;
}

String::String(const char* b) {
    len =  std::strlen(b) ;
    ptr.set(new char[len +1]);
    strcpy(&ptr[0], b);
}

String::String(const SharedPtr<char>& sptr, size_t len) : ptr(sptr), len(len) {}

String&
String::operator= (const String& b) {
    if(this == &b) return *this;
    ptr.release();
    ptr = b.ptr;
    len = b.len;
    return *this;
}

String&
String::operator= (const char* b) {
    len =  std::strlen(b) ;
    ptr.set(new char[len +1]);
    strcpy(&ptr[0], b);
    return *this;
}

String
operator+ (const String& a, const String& b) {
    SharedPtr<char> new_str(new char[a.len + b.len + 1]);
    memcpy(&new_str[0],     &a[0], a.len);
    strcpy(&new_str[a.len], &b[0]);
    return String(new_str, a.len + b.len);
}

char&
String::operator[] (size_t index) {
    return ptr[index];
}

const char&
String::operator[] (size_t index) const {
    return ptr[index];
}

const char*
String::c_str() const {
    return &ptr[0];
}

ostream& operator<< (ostream& os, const String& string) {
    const char* pch = &string[0];
    size_t l = string.len;
    while(l--) {
        os << *pch++;
    }
    return os;
}

istream& operator>> (istream& is, String& string) {
    std::string buffer;
    std::string tmp;

    while(is >> tmp) {
        buffer.append(tmp + " ");
    }

    string = buffer.c_str();
    return is;
}


}
