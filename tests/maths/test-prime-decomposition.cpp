#include <cassert>
#include <vector>

#include "maths/prime-decomposition.hpp"
#include "test-done.hpp"
#include "test-prime-decomposition.hpp"

void testPrimeDecomposition()
{
    SieveOfEratosthenes sieve(1000);

    assert(getPrimeDecomposition(2 * 2 * 2 * 3 * 5 * 5 * 13, sieve) ==
        (std::vector<std::pair<int, int>> {
            {2, 3},
            {3, 1},
            {5, 2},
            {13, 1}
        })
    );

    show_test_done("Prime decomposition");
}
