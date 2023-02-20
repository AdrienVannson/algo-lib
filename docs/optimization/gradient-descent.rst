Gradient Descent
================

:cpp:class:`GradientDescent` is useful to minimize a function. It implements a
gradient descent in which the step length is choosen automatically using
Armijo's inequality, that is if :math:`x_{k+1} = x_k - \alpha \nabla(f)(x_k)`, then
:math:`\alpha` must verify:

.. math::
    f(x_k - \alpha \nabla(f)(x_k)) \leq f(x_k) - c \times \alpha \times \| \nabla(f)(x_k) \| ^2

The constant :math:`c` is :math:`10^{-4}` by default, but it can be ajusted.

..  code-block:: c++
    :caption: Exemple -- Minimization of the Rosenbrock function

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

.. doxygenclass:: GradientDescent