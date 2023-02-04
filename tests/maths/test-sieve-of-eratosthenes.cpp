#include <cassert>

#include "maths/sieve-of-eratosthenes.hpp"
#include "test-done.hpp"
#include "test-sieve-of-eratosthenes.hpp"

void testSieveOfEratosthenes()
{
    SieveOfEratosthenes s0(0), s1(1);
    assert(s0.primeCount() == 0);
    assert(s1.primeCount() == 0);

    SieveOfEratosthenes s(21);
    assert(s.primeCount() == 8);
    assert(s.nthPrime(0) == 2);
    assert(s.nthPrime(1) == 3);
    assert(s.nthPrime(2) == 5);
    assert(s.nthPrime(3) == 7);
    assert(s.nthPrime(4) == 11);
    assert(s.nthPrime(5) == 13);
    assert(s.nthPrime(6) == 17);
    assert(s.nthPrime(7) == 19);

    show_test_done("Sieve of Eratosthenes");
}
