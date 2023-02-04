#include <cassert>

#include "test-matrix.hpp"
#include "maths/matrix.hpp"
#include "test-done.hpp"

void test_matrix()
{
    Matrix<int> A = 2 * Matrix<int>::identity(2);
    Matrix<int> B(2, 2);
    B.set(0, 1, 3);

    Matrix<int> C({{2, 3}, {0, 2}});

    assert(A + B == C);

    show_test_done("Matrix");
}
