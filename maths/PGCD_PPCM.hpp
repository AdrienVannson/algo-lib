#ifndef PGCD_PPCM_HPP
#define PGCD_PPCM_HPP

#include "global.hpp"

int PGCD (const int a, const int b)
{
    if (a == 0) return b;
    return PGCD(b%a, a);
}

array<int,3> PGCD_bezout (const int x, const int y) // {pgcd, a, b} tels que ax+by=pgcd
{
    if (y == 0) return {x, 1, 0};
    const array<int,3> suivant = PGCD_bezout(y, x%y);
    return {suivant[0], suivant[2], suivant[1] - (x/y)*suivant[2]};
}

int PPCM (const int a, const int b)
{
    return a * b / PGCD(a, b);
}


#endif // PGCD_PPCM_HPP
