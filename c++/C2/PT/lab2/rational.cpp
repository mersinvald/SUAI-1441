#include "rational.hpp"
#include "mmath.hpp"
#include <cmath>
#include <utility>
#include <type_traits>
#include <assert.h>


namespace msvd {
namespace math {


Rational::Rational() : _num(0), _denum(0), _dec(0) {}
Rational::Rational(int num, int denum) : _num(num), _denum(denum), _dec(0) {
    Simplify();
}

void
Rational::Rationalize() {
    _dec += _num / _denum;
    _num  = _num % _denum;
}

void
Rational::Simplify() {
    Rationalize();

    // Find greatest common divisor
    int gcd = GCD(_num, _denum);

    // Divide both numenator and denumenator by gcd
    _num   /= gcd;
    _denum /= gcd;
}

Rational&
Rational::operator=(const Rational& from) {
    _num   = from._num;
    _denum = from._denum;
    _dec   = from._dec;
    return *this;
}

Rational
operator+ (const Rational& a, const Rational& b) {
    int a_num = a._num + a._dec * a._denum;
    int b_num = b._num + b._dec * b._denum;
    int a_den = a._denum;
    int b_den = b._denum;

    a_num *= b_den;
    b_num *= a_den;

    return Rational(a_num + b_num, a_den * b_den);
}

Rational
operator+ (const Rational& a, int b) {
    b *= a._denum;
    return Rational(a._num + b, a._denum);
}

Rational
operator+ (int b, const Rational& a) {
    return operator+(a, b);
}

Rational
operator- (const Rational& a, const Rational& b) {
    int a_num = a._num + a._dec * a._denum;
    int b_num = b._num + b._dec * b._denum;
    int a_den = a._denum;
    int b_den = b._denum;

    a_num *= b_den;
    b_num *= a_den;

    return Rational(a_num - b_num, a_den * b_den);
}

Rational
operator- (const Rational& a, int b) {
    b *= a._denum;
    return Rational(a._num + b, a._denum);
}

Rational
operator- (int b, const Rational& a) {
    b *= a._denum;
    return Rational(a._num + b, a._denum);
}

Rational
operator* (const Rational& a, const Rational& b) {
    int a_num = a._num + a._dec * a._denum;
    int b_num = b._num + b._dec * b._denum;
    return Rational(a_num * b_num, a._denum * b._denum);
}

Rational
operator* (const Rational& a, int b) {
    return Rational(a._num * b, a._denum);
}

Rational
operator* (int b, const Rational& a) {
    return Rational(a._num * b, a._denum);
}

Rational
operator/ (const Rational& a, const Rational& b) {
    int a_num = a._num + a._dec * a._denum;
    int b_num = b._num + b._dec * b._denum;
    return Rational(a_num * b._denum, b_num * a._denum);
}

Rational
operator/ (const Rational& a, int b) {
    return Rational(a._num, a._denum * b);
}

Rational
operator/ (int b, const Rational& a) {
    return Rational(a._num, a._denum * b);
}

std::ostream&
operator<<(std::ostream& os, const Rational& obj) {
    return os << ((obj._dec) ? std::to_string(obj._dec) + "+" : "") << obj._num << "/" << obj._denum;
}

std::istream&
operator>>(std::istream& is, Rational& obj) {
    is >> obj._num >> obj._denum;
    obj.Simplify();
    return is;
}

} // math
} // msvd
