#include "test-intersections.hpp"

#include <cassert>

void testIntersections()
{
    using Fr = Fraction<long long>;
    using Vec = Vect2<Fr>;
    using Lin = Line<Fr>;

    auto inter1 =
        getIntersection(Lin(Vec(0, 1), Vec(1, 4)), Lin(Vec(2, 7), Vec(3, 10)));
    assert(inter1.type() == Shape<Fr>::LINE);

    auto inter2 =
        getIntersection(Lin(Vec(3, 1), Vec(4, 4)), Lin(Vec(2, 7), Vec(3, 10)));
    assert(inter2.type() == Shape<Fr>::EMPTY);

    auto inter3 =
        getIntersection(Lin(Vec(1, 1), Vec(5, 3)), Lin(Vec(5, 2), Vec(8, 1)));
    assert(inter3.type() == Shape<Fr>::POINT);
    assert(inter3.point() == Vec(Fr(19, 5), Fr(12, 5)));

    showTestDone("Intersection");
}
