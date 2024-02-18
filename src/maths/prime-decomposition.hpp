#pragma once

#include <vector>

#include "sieve-of-eratosthenes.hpp"

/// \brief Compute the prime decomposition of a positive integer n.
/// @returns A vector containing all the factors of n in increasing order, with
// their power. If n = p_1^a_1 * ... * p_m^a_m with p_1 < ... < p_m primes and
// a_1, ..., a_m >= 1, it returns [(p_1, a_1), ..., (p_m, a_m)].
std::vector<std::pair<int, int>>
getPrimeDecomposition(const int n, const SieveOfEratosthenes &sieve);
