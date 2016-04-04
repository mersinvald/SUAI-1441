/* Originally written by Mike Lubinets, 2016
 * See LICENSE */

#ifndef RATIONAL_H
#define RATIONAL_H
#include <stdint.h>
#include <iostream>
#include <type_traits>
#include <cmath>

namespace msvd {
namespace math {

class Rational {
public:
    Rational();
    Rational(int num, int denum);
    Rational(const Rational&) = default;

    Rational& operator= (const Rational& from);

    template<typename T>
    Rational& operator= (T from) {
        static_assert(std::is_arithmetic<T>::value,
                      "Arithmetic value is required");
        if(std::is_integral<T>::value) {
            _dec   = from;
            _num   = 1;
            _denum = 1;
        } else {
            // Extracting integral and exponent values
            T i, f;
            f = std::modf(from, &i);

            _denum = 1000;
            _num   = static_cast<int>(round(f * 1000.0));
            _dec   = static_cast<int>(i);
        }
        Simplify();
        return *this;
    }

    /* Addition */

    friend Rational operator+ (const Rational& a, const Rational& b);
    friend Rational operator+ (const Rational& a, int b);
    friend Rational operator+ (int b, const Rational& a);

    /* Substraction */

    friend Rational operator- (const Rational& a, const Rational& b);
    friend Rational operator- (const Rational& a, int b);
    friend Rational operator- (int b, const Rational& a);

    /* Multiplication */

    friend Rational operator* (const Rational& a, const Rational& b);
    friend Rational operator* (const Rational& a, int b);
    friend Rational operator* (int b, const Rational& a);

    /* Division */

    friend Rational operator/ (const Rational& a, const Rational& b);
    friend Rational operator/ (const Rational& a, int b);
    friend Rational operator/ (int b, const Rational& a);

    /* Streams */

    friend std::ostream& operator << (std::ostream& os, const Rational& obj);
    friend std::istream& operator >> (std::istream& is, Rational& obj);

    /* Getters */

private:
    void Rationalize();
    void Simplify();

    int      _num;    // Numenator
    int      _denum;  // Denumenator
    unsigned _dec;    // Integer
};

} // math
} // msvd

#endif // RATIONAL_H
