#include <cassert>

#include "optimization/gradient-descent.hpp"
#include "optimization/gradient.hpp"
#include "test-done.hpp"

#include "test-gradient-descent.hpp"

void test_gradient_descent()
{
    // Declare a function and its gradient
    const int n = 8;

    const auto rosenbrock = [](const Vect<double> &x) {
        const double a = 1;
        const double b = 100;

        double sum = 0.;

        for (int i = 0; i < n - 1; i++) {
            const double t = x(i + 1) - x(i)*x(i);
            sum += b * t * t;
            sum += (a - x(i)) * (a - x(i));
        }

        return sum;
    };

    const auto grad = ForwardGradient<decltype(rosenbrock)>(rosenbrock, 1e-7);

    // Create a gradient descent
    GradientDescent<decltype(rosenbrock), decltype(grad)> gradient_descent(rosenbrock, grad, Vect<double>(n));

    // Optimize
    gradient_descent.optimize(20000, 1e-6);

    // Check the results
    assert(gradient_descent.value() <= 1e-8);

    for (int i = 0; i < n; i++) {
        assert(std::abs(gradient_descent.x()(i) - 1) <= 1e-4);
    }

    show_test_done("Gradient descent");
}
