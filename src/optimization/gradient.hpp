#ifndef GRADIENT_HPP
#define GRADIENT_HPP

#include "maths/vect.hpp"

/// \brief Functor computing the gradient of a function with a given value of
/// epsilon using the method of forward gradient. The function f is evaluated
/// (n + 1) times, where n is the dimension of the space.
template<typename F>
class ForwardGradient {
public:
    ForwardGradient(const F &f, const double epsilon) :
        m_f(f),
        m_eps(epsilon)
    {}

    Vect<double> operator()(Vect<double> x) const
    {
        Vect<double> grad(x.size());

        const double coef = 1. / m_eps;
        const double f_x = m_f(x);

        for (int i = 0; i < x.size(); i++) {
            const double x_i = x(i);

            x.set(i, x_i + m_eps);
            const double f_after = m_f(x);
            x.set(i, x_i);

            grad.set(i, coef * (f_after - f_x));
        }

        return grad;
    }

private:
    F m_f;
    double m_eps;
};

/// \brief Functor computing the gradient of a function with a given value of
/// epsilon using the method of backward gradient. The function f is evaluated
/// (n + 1) times, where n is the dimension of the space.
template<typename F>
class BackwardGradient {
public:
    BackwardGradient(const F &f, const double epsilon) :
        m_f(f),
        m_eps(epsilon)
    {}

    Vect<double> operator()(Vect<double> x) const
    {
        Vect<double> grad(x.size());

        const double coef = 1. / m_eps;
        const double f_x = m_f(x);

        for (int i = 0; i < x.size(); i++) {
            const double x_i = x(i);

            x.set(i, x_i - m_eps);
            const double f_before = m_f(x);
            x.set(i, x_i);

            grad.set(i, coef * (f_x - f_before));
        }

        return grad;
    }

private:
    F m_f;
    double m_eps;
};

/// \brief Functor computing the gradient of a function with a given value of
/// epsilon using the method of symetric gradient. The function f is evaluated
/// 2n times, where n is the dimension of the space. However, the method is
/// more precise than the others.
template<typename F>
class SymetricGradient {
public:
    SymetricGradient(const F &f, const double epsilon) :
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
