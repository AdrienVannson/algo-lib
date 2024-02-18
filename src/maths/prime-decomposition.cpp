#include "prime-decomposition.hpp"

#include <cassert>

std::vector<std::pair<int, int>> getPrimeDecomposition(int n, const SieveOfEratosthenes &sieve)
{
    assert(n >= 1);

    std::vector<std::pair<int, int>> factors;

    for (int i = 0; n > 1 && i < sieve.primeCount(); i++) {
        const int p = sieve.nthPrime(i);

        int a = 0;
        while (n % p == 0) {
            a++;
            n /= p;
        }

        if (a > 0) {
            factors.push_back(std::make_pair(p, a));
        }
    }

    assert(n == 1);
    return factors;
}
