#include "simplex.hpp"
#include "constants.hpp"

#include <iostream>
using namespace std;

template<class T>
Simplex<T>::Simplex(const int variables_count) :
    m_outcome(NOT_FINISHED), m_variables_count(variables_count)
{}

// Σ a_j x_j >= b
template<class T>
void Simplex<T>::add_greater_than(std::vector<T> coefs, T cst)
{
    // Create a new variable
    const int new_var = m_variables_count;
    m_variables_count++;

    // Add the constraint x = Σ a_j x_j - b
    Constraint constr;
    constr.var_index = new_var;
    constr.coefs = coefs;
    constr.cst = -cst;

    m_constraints.push_back(constr);
}

// Σ a_j x_j <= b
template<class T>
void Simplex<T>::add_lower_than(std::vector<T> coefs, T cst)
{
    for (T &coef : coefs) {
        coef = -coef;
    }
    add_greater_than(coefs, -cst);
}

template<class T>
void Simplex<T>::maximize(const std::vector<T> &coefs)
{
    assert(m_outcome == NOT_FINISHED);

    // Initialize the function to optimize
    m_to_optimize.var_index = -1;
    m_to_optimize.coefs = coefs;
    m_to_optimize.cst = Constants<T>::zero();

    // Add zeros for the new variables to the constraints and the funcction to
    // optimize
    resize_constraints();
    m_to_optimize.coefs.resize(m_variables_count, Constants<T>::zero());

#ifdef SIMPLEX_VERBOSE
    cerr << "Starting simplex\n\n";
    print_constraints();
    cerr << "\n";
#endif

    Outcome outcome = NOT_FINISHED;

    while (outcome == NOT_FINISHED) {
        outcome = one_step();
    }

    m_outcome = outcome;
}

template<class T>
void Simplex<T>::minimize(const std::vector<T> &coefs)
{
    std::vector<T> new_coefs = coefs;
    for (T &coef : new_coefs) {
        coef = -coef;
    }

    maximize(new_coefs);
}

template<class T>
typename Simplex<T>::Outcome Simplex<T>::outcome() const
{
    return m_outcome;
}

template<class T>
T Simplex<T>::optimal() const
{
    return m_to_optimize.cst;
}

template<class T>
typename Simplex<T>::Outcome Simplex<T>::one_step()
{
    // Choose an entering variable
    int entering = -1;

    for (int i = 0; i < m_variables_count; i++) {
        if (m_to_optimize.coefs[i] > Constants<T>::zero()) {
            entering = i;
            break;
        }
    }

    if (entering == -1) {
        return OPTIMAL_SOLUTION;
    }

    // Choose a leaving variable
    int leaving = -1;
    T val_min = Constants<T>::zero();

    for (const Constraint &constr : m_constraints) {
        if (constr.coefs[entering] < Constants<T>::zero()) {
            // We can increase the entering variable to at most val
            const T val = constr.cst / -constr.coefs[entering];

            if (leaving == -1 || val < val_min) {
                leaving = constr.var_index;
                val_min = val;
            }
        }
    }

    if (leaving == -1) {
        return UNBOUNDED;
    }

    // Update the constraints
    int constraint_entering = -1;

    for (int i = 0; i < (int)m_constraints.size(); i++) {
        Constraint &constr = m_constraints[i];

        if (constr.var_index == leaving) {
            const T divider = -constr.coefs[entering];

            constr.coefs[entering] = Constants<T>::zero();
            constr.coefs[leaving] = -Constants<T>::one();

            constr.var_index = entering;

            assert(constr.cst / divider == val_min);

            constr.cst = val_min;
            for (int j = 0; j < m_variables_count; j++) {
                constr.coefs[j] /= divider;
            }

            constraint_entering = i;
            break;
        }
    }

    for (int i = 0; i < (int)m_constraints.size(); i++) {
        Constraint &constr = m_constraints[i];

        if (constr.var_index != entering) {
            constr.cst +=
                constr.coefs[entering] * m_constraints[constraint_entering].cst;
            for (int j = 0; j < m_variables_count; j++) {
                constr.coefs[j] += constr.coefs[entering]
                    * m_constraints[constraint_entering].coefs[j];
            }

            constr.coefs[entering] = Constants<T>::zero();
        }
    }

    // Update the objective function to remove the entering variable
    m_to_optimize.cst +=
        m_to_optimize.coefs[entering] * m_constraints[constraint_entering].cst;
    for (int i = 0; i < m_variables_count; i++) {
        m_to_optimize.coefs[i] += m_to_optimize.coefs[entering]
            * m_constraints[constraint_entering].coefs[i];
    }
    m_to_optimize.coefs[entering] = Constants<T>::zero();

#ifdef SIMPLEX_VERBOSE
    // Display the choices made and the resulting system
    cerr << "Entering: x_" << entering << "\tLeaving: x_" << leaving << "\n\n";
    print_constraints();
    cerr << "\n";
#endif

    return NOT_FINISHED;
}

template<class T>
void Simplex<T>::print_constraints()
{
    cerr << "Maximizing " << m_to_optimize.cst;
    for (int i = 0; i < m_variables_count; i++) {
        if (m_to_optimize.coefs[i] != Constants<T>::zero()) {
            cerr << " + " << m_to_optimize.coefs[i] << " x_" << i;
        }
    }
    cerr << " subject to:\n";

    for (const Constraint &constr : m_constraints) {
        cerr << "| x_" << constr.var_index << " = " << constr.cst;
        for (int i = 0; i < m_variables_count; i++) {
            if (constr.coefs[i] != Constants<T>::zero()) {
                cerr << " + " << constr.coefs[i] << " x_" << i;
            }
        }
        cerr << "\n";
    }
}

template<class T>
void Simplex<T>::resize_constraints()
{
    for (Constraint &constr : m_constraints) {
        constr.coefs.resize(m_variables_count, Constants<T>::zero());
    }
}
