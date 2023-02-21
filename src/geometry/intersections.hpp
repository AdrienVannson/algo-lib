#pragma once

#include <cassert>
#include <utility>
#include <vector>

#include "constants.hpp"
#include "line.hpp"
#include "segment.hpp"
#include "shape.hpp"
#include "vect2.hpp"
#include "vect3.hpp"

/// \brief Computes the intersection of two lines.
template<class T>
Shape<T> getIntersection(const Line<T> line1, const Line<T> line2)
{
    const T det = line1.b() * line2.a() - line1.a() * line2.b();

    if (det == Constants<T>::zero()) {
        // Test if the two lines are the same
        Vect3<T> v1(line1.a(), line1.b(), line1.c());
        Vect3<T> v2(line2.a(), line2.b(), line2.c());

        if ((v1 ^ v2).isNull()) {
            return Shape<T>(line1);
        } else {
            return Shape<T>();
        }
    }

    const T x = line2.b() * line1.c() - line1.b() * line2.c();
    const T y = line1.a() * line2.c() - line2.a() * line1.c();

    return Shape<T>(Vect2<T>(x / det, y / det));
}

template<class T>
Shape<T> getIntersection(const Line<T> line, const Segment<T> seg)
{
    const Shape<T> inter = getIntersection(line, seg.toLine());

    if (inter.type() == Shape<T>::LINE) {
        return Shape<T>(seg);
    }
    if (inter.type() == Shape<T>::EMPTY || !seg.containsPoint(inter.point())) {
        return Shape<T>();
    }
    return Shape<T>(inter);
}
