#include "gcd-lcm.hpp"

#include <complex>

long long getGCD(long long a, long long b)
{
    if (a < 0) a *= -1;
    if (b < 0) b *= -1;
    if (b > a) std::swap(a, b);

    while (b != 0) {
        const long long t = b;
        b = a % b;
        a = t;
    }

    return a;
}

std::array<long long, 3> getGCDBezout(long long a, long long b)
{
    if (a < 0 || b < 0) {
        std::array<long long, 3> res = getGCDBezout(std::abs(a), std::abs(b));
        if (a < 0) res[1] *= -1;
        if (b < 0) res[2] *= -1;
        return res;
    }

    if (b > a) {
        std::array<long long, 3> res = getGCDBezout(b, a);
        std::swap(res[1], res[2]);
        return res;
    }

    long long u1 = 1, v1 = 0; // a = aInit*u1 + bInit*v1
    long long u2 = 0, v2 = 1; // b = aInit*u2 + bInit*v2

    while (b != 0) {
        const long long t = b;
        const long long t_u = u2;
        const long long t_v = v2;

        const long long q = a / b;

        u2 = u1 - q * u2;
        v2 = v1 - q * v2;
        b = a % b;

        a = t;
        u1 = t_u;
        v1 = t_v;
    }

    return {a, u1, v1};
}

long long getLCM(long long a, long long b)
{
    return std::abs(a * b) / getGCD(a, b);
}
