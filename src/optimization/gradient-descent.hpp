#pragma once

#include "maths/vect.hpp"

// F: type of f
// G: type of grad(f)
template<typename F, typename G>
class GradientDescent
{
public:
    GradientDescent(F f, G grad, const Vect<double> &startingPoint) :
        m_f(f),
        m_grad(grad),
        m_x(startingPoint)
    {}

    /// \brief Sets the point at which the gradient descent will start
    inline void setStartingPoint(const Vect<double> &x)
    {
        m_x = x;
    }

    /// \brief Starts the optimization
    /// @param maxIterationsCount The maximal number of iterations that the
    /// algorithm can perform
    /// @param tolerance Once the norm of the gradient is lower than this value,
    /// the gradient descent stops.
    /// @param armijoCoef The value of c in the Armijo's inequality.
    /// @param updateFactor The value by which the step length is multiplied
    /// or divided
    void optimize(const int maxIterationsCount, const double tolerance,
                  const double armijoCoef = 1e-4, const double updateFactor = 1.3);

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
void GradientDescent<F, G>::optimize(const int maxIterationsCount,
    const double tolerance, const double armijoCoef, const double updateFactor)
{
    const double updateFactorInv = 1. / updateFactor;

    double alpha = 1; // Step length

    for (int it = 0; it < maxIterationsCount; it++) {
        const double f_x = m_f(m_x);
        const Vect<double> grad = m_grad(m_x);
        const double gradSquaredNorm = grad.squared_norm();

        if (gradSquaredNorm < tolerance * tolerance) break;

        // Update the step length
        if (m_f(m_x - alpha * grad) <= f_x - armijoCoef * alpha * gradSquaredNorm) {
            alpha *= updateFactor;

            // While Armijo's condition is verified, go further
            while (m_f(m_x - alpha * grad) <= f_x - armijoCoef * alpha * gradSquaredNorm) {
                alpha *= updateFactor;
            }

            alpha *= updateFactorInv;
        } else {
            alpha *= updateFactorInv;

            // Go nearer until Armijo's condition is verified
            while (m_f(m_x - alpha * grad) > f_x - armijoCoef * alpha * gradSquaredNorm) {
                alpha *= updateFactorInv;
            }
        }

        m_x -= alpha * grad;
    }
}
