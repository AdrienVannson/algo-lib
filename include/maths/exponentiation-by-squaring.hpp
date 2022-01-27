#ifndef EXPONENTIATION_BY_SQUARING_HPP
#define EXPONENTIATION_BY_SQUARING_HPP

#include <cassert>

/// \brief Exponentiation by squaring (p must be strictly positive)
template<class T>
T getPower(const T &x, const int p)
{
    assert(p > 0);

    if (p == 1) return x;
    if (p % 2 == 1) return x * getPower(x * x, p / 2);
    return getPower(x * x, p / 2);
}

#endif // EXPONENTIATION_BY_SQUARING_HPP
