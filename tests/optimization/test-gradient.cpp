#include "test-gradient.hpp"
#include "test-done.hpp"

#include <cassert>
#include <cmath>

#include "maths/vect.hpp"
#include "optimization/gradient.hpp"

void test_gradient()
{
    const auto f = [](const Vect<double> &x) {
        return sin(x(0));
    };

    const auto forward_grad = ForwardGradient<decltype(f)>(f, 1e-7);
    const double forward_diff = std::abs(forward_grad(std::vector<double>{1})(0) - cos(1));
    assert(1e-8 <= forward_diff && forward_diff <= 1e-7);

    const auto backward_grad = BackwardGradient<decltype(f)>(f, 1e-7);
    const double backward_diff = std::abs(backward_grad(std::vector<double>{1})(0) - cos(1));
    assert(1e-8 <= backward_diff && backward_diff <= 1e-7);

    // Symetric gradient is more precise
    const auto symetric_grad = SymetricGradient<decltype(f)>(f, 1e-7);
    const double symetric_diff = std::abs(symetric_grad(std::vector<double>{1})(0) - cos(1));
    assert(1e-10 <= symetric_diff && symetric_diff <= 1e-9);

    show_test_done("Gradient");
}
