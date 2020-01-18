#ifndef EXPONENTIATION_RAPIDE_HPP
#define EXPONENTIATION_RAPIDE_HPP

#include "global.hpp"

template<class T>
T getPuissance (const T &x, const int puissance)
{
    assert(puissance > 0);

    if (puissance == 1) return x;
    if (puissance % 2 == 1) return x * getPuissance(x * x, (puissance-1) / 2);
    return getPuissance(x * x, puissance / 2);
}

#endif // EXPONENTIATION_RAPIDE_HPP
