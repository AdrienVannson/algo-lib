#ifndef GRADIENT_HPP
#define GRADIENT_HPP

#include "maths/vect.hpp"

/// \brief Functor computing the gradient of a function with a given value of
/// epsilon
template<typename F>
class Gradient {
public:
    Gradient(const F &f, const double epsilon) :
        m_f(f),
        m_eps(epsilon)
    {}

    Vect<double> operator()(Vect<double> x) const
    {
        Vect<double> grad(x.size());

        const double coef = 1. / (2. * m_eps);

        for (int i = 0; i < x.size(); i++) {
            const double x_i = x(i);

            x.set(i, x_i + m_eps);
            const double f_after = m_f(x);

            x.set(i, x_i - m_eps);
            const double f_before = m_f(x);

            x.set(i, x_i);

            grad.set(i, coef * (f_after - f_before));
        }

        return grad;
    }

private:
    F m_f;
    double m_eps;
};

#endif // GRADIENT_HPP
