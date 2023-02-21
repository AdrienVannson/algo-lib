#pragma once

#include <array>

long long getGCD(long long a, long long b);

/// \brief Returns {gcd, u, v} such that gcd = a*u + b*v
std::array<long long, 3> getGCDBezout(long long a, long long b);

long long getLCM(long long a, long long b);
