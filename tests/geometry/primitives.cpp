#include "primitives.hpp"
#include "src/geometry/primitives.hpp"

#include <cassert>

using Vec = Vect2<int>;

void testIntersection()
{
    auto inter1 = getIntersection(Vec(0, 1), Vec(1, 4), Vec(2, 7), Vec(3, 10));
    assert(inter1.first == IntersectionType::LINE);

    auto inter2 = getIntersection(Vec(3, 1), Vec(4, 4), Vec(2, 7), Vec(3, 10));
    assert(inter2.first == IntersectionType::EMPTY);

    auto inter3 = getIntersection(Vec(1, 1), Vec(5, 3), Vec(5, 2), Vec(8, 1));
    assert(inter3.first == IntersectionType::POINT);
    assert((inter3.second - Vect2<double>(3.8, 2.4)).norm() <= 1e-5);

    showTestDone("Intersection");
}
