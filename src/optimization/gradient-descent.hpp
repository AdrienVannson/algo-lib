#ifndef GRADIENTDESCENT_HPP
#define GRADIENTDESCENT_HPP

#include "maths/vect.hpp"

// F: type of f
// G: type of grad(f)
template<typename F, typename G>
class GradientDescent
{
public:
    GradientDescent(F f, G grad, const Vect<double> &starting_point) :
        m_f(f),
        m_grad(grad),
        m_x(starting_point)
    {}

    /// \brief Sets the point at which the gradient descent will start
    inline void set_starting_point(const Vect<double> &x)
    {
        m_x = x;
    }

    /// \brief Starts the optimization
    /// @param max_iterations_count The maximal number of iterations that the
    /// algorithm can perform
    /// @param tolerance Once the norm of the gradient is lower than this value,
    /// the gradient descent stops.
    /// @param armijo_coef The value of c in the Armijo's inequality.
    /// @param update_factor The value by which the step length is multiplied
    /// or divided
    void optimize(const int max_iterations_count, const double tolerance,
                  const double armijo_coef = 1e-4, const double update_factor = 1.3);

    /// \brief Returns the current value of f
    double value() const
    {
        return m_f(m_x);
    }

    /// \brief Returns the current value of x (the position of the minimum)
    const Vect<double>& x() const
    {
        return m_x;
    }

private:
    F m_f;
    G m_grad; // Gradient of f
    Vect<double> m_x;
};

template<typename F, typename G>
void GradientDescent<F, G>::optimize(const int max_iterations_count,
    const double tolerance, const double armijo_coef, const double update_factor)
{
    const double update_factor_inv = 1. / update_factor;

    double alpha = 1; // Step length

    for (int it = 0; it < max_iterations_count; it++) {
        const double f_x = m_f(m_x);
        const Vect<double> grad = m_grad(m_x);
        const double grad_squared_norm = grad.squared_norm();

        if (grad_squared_norm < tolerance * tolerance) break;

        // Update the step length
        if (m_f(m_x - alpha * grad) <= f_x - armijo_coef * alpha * grad_squared_norm) {
            alpha *= update_factor;

            // While Armijo's condition is verified, go further
            while (m_f(m_x - alpha * grad) <= f_x - armijo_coef * alpha * grad_squared_norm) {
                alpha *= update_factor;
            }

            alpha *= update_factor_inv;
        } else {
            alpha *= update_factor_inv;

            // Go nearer until Armijo's condition is verified
            while (m_f(m_x - alpha * grad) > f_x - armijo_coef * alpha * grad_squared_norm) {
                alpha *= update_factor_inv;
            }
        }

        m_x -= alpha * grad;
    }
}

#endif // GRADIENTDESCENT_HPP
