#ifndef INTERSECTIONS_HPP
#define INTERSECTIONS_HPP

#include <cassert>
#include <utility>
#include <vector>

#include "Vect2.hpp"
#include "constants.hpp"
#include "line.hpp"
#include "segment.hpp"
#include "shape.hpp"

/// \brief Computes the intersection of two lines.
template<class T>
Shape<T> getIntersection(const Line<T> line1, const Line<T> line2)
{
    const Vect2<T> A = line1.A();
    const Vect2<T> B = line1.B();
    const Vect2<T> C = line2.A();
    const Vect2<T> D = line2.B();

    // TODO: assert(A != B && C != D);

    const Vect2<T> AB = B - A;
    const Vect2<T> CD = D - C;

    const T c1 = A.x * B.y - A.y * B.x;
    const T c2 = C.x * D.y - C.y * D.x;

    const T det = AB ^ CD;

    if (det == Constants<T>::zero()) {
        const Vect2<T> AC = C - A;

        if ((AB ^ AC) == Constants<T>::zero()) {
            return Shape<T>(line1);
        } else {
            return Shape<T>();
        }
    }

    const T x = -CD.x * c1 + AB.x * c2;
    const T y = -CD.y * c1 + AB.y * c2;

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

#endif // INTERSECTIONS_HPP
