#ifndef MATH_H
#define MATH_H
#include <assert.h>
#include <type_traits>
#include <utility>

namespace msvd {
namespace math {

// Greatest Common Divisor
template <typename T>
T GCD (T gcd, T b) {
    static_assert(std::is_arithmetic<T>::value,
                  "Arithmetic types required");

    T t;
    if(gcd < b) std::swap(gcd, b);
    while(b) {
        t   = b;
        b   = gcd % b;
        gcd = t;
    }
    return gcd;
}

}
}

#endif // MATH_H
