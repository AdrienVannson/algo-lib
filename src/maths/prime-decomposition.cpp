#include "prime-decomposition.hpp"

#include <cassert>

std::vector<int> getPrimeDecomposition(int n, const SieveOfEratosthenes &sieve)
{
    std::vector<int> decomposition;

    for (int i = 0; n > 1 && i < sieve.primeCount(); i++) {
        const int p = sieve.nthPrime(i);
        decomposition.push_back(0);

        while (n % p == 0) {
            decomposition.back()++;
            n /= p;
        }
    }

    assert(n == 1);
    return decomposition;
}
