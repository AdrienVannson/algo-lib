#include "sieve-of-eratosthenes.hpp"

SieveOfEratosthenes::SieveOfEratosthenes(const int n) : m_isPrime(n, true)
{
    if (n >= 1) {
        m_isPrime[0] = false;

        if (n >= 2) {
            m_isPrime[1] = false;
        }
    }

    for (int p = 2; p < n; p++) {
        if (m_isPrime[p]) {
            m_primes.push_back(p);

            for (int i = 2; i * p < n; i++) {
                m_isPrime[i * p] = false;
            }
        }
    }
}
