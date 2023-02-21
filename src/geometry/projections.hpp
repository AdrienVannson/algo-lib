#pragma once

#include "line.hpp"
#include "vect2.hpp"

template<class T>
Vect2<T> getProjection(const Vect2<T> M, const Line<T> L)
{
    const T a = L.a(), b = L.b(), c = L.c();
    const T x = M.x, y = M.y;

    const T den = a * a + b * b;

    return Vect2<T>(
        (b * b * x - a * b * y - a * c) / den,
        (-a * b * x + a * a * y - b * c) / den
    );
}
