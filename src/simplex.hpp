#ifndef SIMPLEX_HPP
#define SIMPLEX_HPP

#include <vector>

/// \brief Solves a linear problem with the simplex algorithm.
/// The variables are x_0, ..., x_{n-1}
/// For now, all the variables are supposed non-negative.
/// If the preprocessor variable SIMPLEX_VERBOSE is defined, detailed
/// informations about the resolution of the problem are printed on stderr.
template<class T>
class Simplex
{
public:
    enum Outcome
    {
        OPTIMAL_SOLUTION,
        NO_SOLUTION,
        UNBOUNDED,
        NOT_FINISHED // The algorithm needs more iterations (internal state)
    };

    /// \brief Initializes the simplex algorithm to solve a problem with the
    /// given number of variables.
    Simplex(const int variables_count);

    /// \brief Returns the number of variables that the problem contains
    int variables_count() const;

    /// \brief Adds the contraint: Σ a_j x_j >= b
    void add_greater_than(std::vector<T> coefs, T cst);

    /// \brief Adds the contraint: Σ a_j x_j <= b
    void add_lower_than(std::vector<T> coefs, T cst);

    /// \brief Runs the simplex algorithm to maximize Σ a_j x_j subject to the
    /// previously given constraints.
    void maximize(const std::vector<T> &coefs);

    /// \brief Runs the simplex algorithm to minimize Σ a_j x_j subject to the
    /// previously given constraints.
    void minimize(const std::vector<T> &coefs);

    /// \brief Returns the outcome of the simplex (NOT_FINISHED if the algorithm
    /// has not been executed yet)
    Outcome outcome() const;

    /// \brief Returns the optimal value computed by the simplex.
    T optimal_value() const;

    /// \brief Returns the value of a variable in the optimal solution that was found
    T solution_value(const int var) const;

private:
    // Internal representation of a constraint of equality:
    // x_i = b + Σ a_j x_j
    // For all j, if x_j is a basic variable, then A[j] = 0.
    struct Constraint {
        int var_index; // i in the formula
        std::vector<T> coefs; // a in the formula
        T cst; // b in the formula
    };

    // Outcome of the simplex (NOT_FINISHED if the algorithm has not been
    // executed yet)
    Outcome m_outcome;

    // Total number of variables in the problem, including internal variables.
    int m_variables_count;

    // Description of the variables used by the user. They may be different from
    // the non-basic variables, even at the start of the algorithm.
    // TODO

    // The current contraints of the problem
    std::vector<Constraint> m_constraints;

    // The function to optimize (var_index = -1)
    Constraint m_to_optimize;

    /// \brief Returns the next entering variable (-1 if the solution is optimal)
    int choose_entering_variable() const;

    /// \brief Returns the next leaving variable (-1 if the problem is unbounded).
    /// @param entering The entering variable choosen before
    int choose_leaving_variable(const int entering) const;

    /// \brief Executes a transformation of the problem
    void make_exchange(const int entering, const int leaving);

    /// \brief Executes one step of the simplex algorithm
    Outcome one_step();

    /// \brief Prints the current state of the simplex on stderr
    void print_constraints();

    /// \brief Add null coefficients at the end of each constraint to take into
    /// account the new variables.
    void resize_constraints();
};

#endif // SIMPLEX_HPP
