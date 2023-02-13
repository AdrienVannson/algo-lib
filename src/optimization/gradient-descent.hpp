#ifndef GRADIENTDESCENT_HPP
#define GRADIENTDESCENT_HPP

#include "maths/vect.hpp"

// TODO: template to change type of double
// F: type of f
// G: type of grad(f)
template<typename F, typename G>
class GradientDescent
{
public:
    GradientDescent(const int dimensions_count, F f, G grad) :
        m_f(f),
        m_grad(grad),
        m_x(dimensions_count)
    {}

    /// \brief Sets the point at which the gradient descent will start
    inline void set_starting_point(const Vect<double> x)
    {
        m_x = x;
    }

    /// \brief Starts the optimization
    /// @param max_iterations_count
    /// @param armijo_coef is the value of c in the Armijo's inequality.
    /// @param update_factor the value by which the step length is multiplied
    /// or divided
    void optimize(const int max_iterations_count, const double armijo_coef = 1e-4, const double update_factor = 1.3);

    /// \brief Returns the current value of f
    double value() const
    {
        return m_f(m_x);
    }

private:
    F m_f;
    G m_grad; // Gradient of f
    Vect<double> m_x;
};

template<typename F, typename G>
void GradientDescent<F, G>::optimize(const int max_iterations_count,
    const double armijo_coef, const double update_factor)
{
    const double update_factor_inv = 1. / update_factor;

    double alpha = 1; // Step length

    for (int it = 0; it < max_iterations_count; it++) {
        const Vect<double> grad = m_grad(m_x);

        if (grad.norm() < 1e-6) break;

        // Update the step length
        if (m_f(m_x - alpha * grad) <= m_f(m_x) - armijo_coef * alpha * grad.squared_norm()) {
            alpha *= update_factor;

            // While Armijo's condition is verified, go further
            while (m_f(m_x - alpha * grad) <= m_f(m_x) - armijo_coef * alpha * grad.squared_norm()) {
                alpha *= update_factor;
            }

            alpha *= update_factor_inv;
        } else {
            alpha *= update_factor_inv;

            // Go nearer until Armijo's condition is verified
            while (m_f(m_x - alpha * grad) > m_f(m_x) - armijo_coef * alpha * grad.squared_norm()) {
                alpha *= update_factor_inv;
            }
        }

        m_x -= alpha * grad;
    }
}

#endif // GRADIENTDESCENT_HPP
