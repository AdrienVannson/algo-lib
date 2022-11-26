#include "test-simplex.hpp"
#include "maths/Fraction.hpp"
#include "simplex.hpp"
#include "test-done.hpp"

using Fr = Fraction<long long>;

void test_simplex()
{
    {
        Simplex<Fr> simplex(3);
        simplex.add_lower_than({2, 3, 1}, 5);
        simplex.add_lower_than({4, 1, 2}, 11);
        simplex.add_lower_than({3, 4, 2}, 8);

        assert(simplex.outcome() == simplex.NOT_FINISHED);
        simplex.maximize({5, 4, 3});
        assert(simplex.outcome() == simplex.OPTIMAL_SOLUTION);

        assert(simplex.optimal() == Fr(13));
    }

    {
        Simplex<Fr> simplex(3);
        simplex.add_lower_than({2, 3, 1}, 5);
        simplex.add_lower_than({4, 1, 2}, 11);
        simplex.add_lower_than({3, 4, 2}, 8);

        simplex.minimize({-5, -4, -3});
        assert(simplex.optimal() == Fr(13));
    }

    showTestDone("Simplex");
}
