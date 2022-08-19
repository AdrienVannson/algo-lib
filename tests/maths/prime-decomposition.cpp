#include <cassert>

#include "maths/prime-decomposition.hpp"
#include "prime-decomposition.hpp"

void testPrimeDecomposition()
{
    SieveOfEratosthenes sieve(1000);

    assert(
        getPrimeDecomposition(2 * 2 * 2 * 3 * 5 * 5 * 13, sieve)
        == (std::vector<int> {3, 1, 2, 0, 0, 1}));

    showTestDone("Prime decomposition");
}
