#include "test-simplex.hpp"
#include "maths/Fraction.hpp"
#include "simplex.hpp"
#include "test-done.hpp"

using Fr = Fraction<long long>;

void test_simplex()
{
    // Optimal solution (maximize)
    {
        Simplex<Fr> simplex(3);
        simplex.add_lower_than({2, 3, 1}, 5);
        simplex.add_lower_than({4, 1, 2}, 11);
        simplex.add_lower_than({3, 4, 2}, 8);

        assert(simplex.outcome() == simplex.NOT_FINISHED);
        simplex.maximize({5, 4, 3});
        assert(simplex.outcome() == simplex.OPTIMAL_SOLUTION);

        assert(simplex.optimal_value() == Fr(13));
    }

    // Optimal solution (minimize)
    {
        Simplex<Fr> simplex(3);
        simplex.add_lower_than({2, 3, 1}, 5);
        simplex.add_lower_than({4, 1, 2}, 11);
        simplex.add_lower_than({3, 4, 2}, 8);

        simplex.minimize({-5, -4, -3});
        assert(simplex.outcome() == simplex.OPTIMAL_SOLUTION);
        assert(simplex.optimal_value() == Fr(13));
    }

    // Optimal solution (maximize)
    {
        Simplex<Fr> simplex(2);
        simplex.add_lower_than({1, -1}, 1);
        simplex.add_greater_than({1, -2}, -2);
        simplex.maximize({1, 1});

        assert(simplex.outcome() == simplex.OPTIMAL_SOLUTION);
        assert(simplex.optimal_value() == Fr(7));
        assert(simplex.solution_value(0) == Fr(4));
        assert(simplex.solution_value(1) == Fr(3));
    }

    showTestDone("Simplex");
}
