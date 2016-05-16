#ifndef STRING_H
#define STRING_H
#include <stdint.h>
#include <stddef.h>
#include "sharedptr.hpp"

namespace msvd {

using std::istream;
using std::ostream;

class String {
public:
    String();
    String(const String& b);
    String(const char* b);
    String(const SharedPtr<char>& sptr, size_t len);

    String& operator= (const String& b);
    String& operator= (const char* b);

    friend bool operator== (const String& a, const String& b);
    friend bool operator!= (const String& a, const String& b);
    friend bool operator<  (const String& a, const String& b);
    friend bool operator>  (const String& a, const String& b);
    friend bool operator<= (const String& a, const String& b);
    friend bool operator>= (const String& a, const String& b);

    friend String operator+ (const String& a, const String& b);

    char& operator[] (size_t index);
    const char& operator[] (size_t index) const;

    const char* c_str() const;

    friend ostream& operator<< (ostream& os, const String& string);
    friend istream& operator>> (istream& is, String& string);

    // Getters
    size_t   length() const { return len; }

private:
    SharedPtr<char> ptr;
    size_t          len;
};

}
#endif // STRING_H
