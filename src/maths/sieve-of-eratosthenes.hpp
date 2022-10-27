#ifndef SIEVEOFERATOSTHENES_HPP
#define SIEVEOFERATOSTHENES_HPP

#include <vector>

/// \brief Computes the prime numbers lower than an integer n
class SieveOfEratosthenes
{
public:
    SieveOfEratosthenes(const int n);

    /// \brief Returns if k is prime
    inline bool isPrime(const int k) const
    {
        return m_isPrime[k];
    }

    /// \brief Returns the number of prime numbers lower than n
    inline int primeCount() const
    {
        return m_primes.size();
    }

    /// \brief Returns the k-th prime number
    inline int nthPrime(const int k) const
    {
        return m_primes[k];
    }

    /// \brief Returns a vector containing all the prime numbers
    /// lower than n, in ascending order
    inline const std::vector<int> &primes() const
    {
        return m_primes;
    }

private:
    std::vector<bool> m_isPrime;
    std::vector<int> m_primes;
};

#endif // SIEVEOFERATOSTHENES_HPP
