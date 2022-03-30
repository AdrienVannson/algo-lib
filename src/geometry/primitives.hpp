#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include <utility>

#include "Vect2.hpp"
#include "constants.hpp"

enum IntersectionType { POINT, EMPTY, LINE };

/// \brief Computes the intersection of (AB) and (CD). The point of intersection
/// is set to its default value if the lines are parallel
template<class T>
std::pair<IntersectionType, Vect2<double>> getIntersection(
    const Vect2<T> A, const Vect2<T> B, const Vect2<T> C, const Vect2<T> D)
{
    // TODO: assert(A != B && C != D);

    const Vect2<T> AB = B - A;
    const Vect2<T> CD = D - C;

    const T c1 = A.x * B.y - A.y * B.x;
    const T c2 = C.x * D.y - C.y * D.x;

    const T det = AB ^ CD;

    if (det == Constants<T>::zero()) {
        const Vect2<T> AC = C - A;

        if ((AB ^ AC) == 0) {
            return std::make_pair(LINE, Vect2<double>());
        } else {
            return std::make_pair(EMPTY, Vect2<double>());
        }
    }

    const double x = -CD.x * c1 + AB.x * c2;
    const double y = -CD.y * c1 + AB.y * c2;

    return std::make_pair(POINT, Vect2<double>(x / det, y / det));
}

#endif // PRIMITIVES_HPP
