#include <cassert>

#include "test-done.hpp"
#include "test-projections.hpp"

void testProjections()
{
    using Fr = Fraction<long long>;
    using Vec = Vect2<Fr>;
    using Lin = Line<Fr>;

    assert(
        getProjection(Vec(8, 2), Lin(1, -3, 6)) == Vec(Fr(72, 10), Fr(44, 10))
    );

    show_test_done("Projection");
}
