#pragma once

#include <vector>

#include "sieve-of-eratosthenes.hpp"

/// \brief Returns the list of the exponents in the prime decomposition of n
/// (the first value if the power of 2 in the decomposition).
std::vector<int>
getPrimeDecomposition(const int n, const SieveOfEratosthenes &sieve);
