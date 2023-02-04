#include "test-utility.hpp"
#include "test-done.hpp"
#include "utility.hpp"

#include <cassert>
#include <vector>

void test_utility()
{
    const long long n = 1000000;

    std::vector<long long> squares = apply_fct<int, long long>(
        range(n + 1),
        [](int x) { return (long long)x * x; }
    );

    assert(sum(squares) == n * (n+1) * (2*n+1) / 6);

    show_test_done("Utility");
}
