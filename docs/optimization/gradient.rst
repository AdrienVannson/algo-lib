Gradient
========

The classes :cpp:class:`ForwardGradient`, :cpp:class:`BackwardGradient` and :cpp:class:`SymetricGradient` allow to approximate the value of the gradient of a differentiable function.

..  code-block:: c++
    :caption: Exemple -- Gradient of the sinus function

    // Create the function
    const auto f = [](const Vect<double> &x) {
        return sin(x(0));
    };

    // Create its gradient
    const auto grad = ForwardGradient<decltype(f)>(f, 1e-7);

    // Compute the value of the gradient at a given point
    const double value = grad(std::vector<double>{1})(0);

.. doxygenfile:: gradient.hpp