#include "simplex.hpp"
#include "constants.hpp"

#include <iostream>
using namespace std;

template<class T>
Simplex<T>::Simplex(const int variables_count) :
    m_outcome(NOT_FINISHED), m_variables_count(variables_count)
{}

template<class T>
int Simplex<T>::variables_count() const
{
    return m_variables_count - m_constraints.size();
}

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

    // Test if a first phase is needed to find an admissible solution
    bool first_phase = false;
    for (Constraint constr : m_constraints) {
        if (constr.cst < Constants<T>::zero()) {
            first_phase = true;
            break;
        }
    }

    if (first_phase) {
        Simplex<T> first_phase(m_variables_count + 1);
        const int new_var = m_variables_count;

        first_phase.m_constraints = m_constraints;
        first_phase.resize_constraints();

        for (Constraint &constr : first_phase.m_constraints) {
            constr.coefs[new_var] = Constants<T>::one();
        }

        first_phase.m_to_optimize.var_index = -1;
        first_phase.m_to_optimize.cst = Constants<T>::zero();
        first_phase.m_to_optimize.coefs.resize(m_variables_count + 1, Constants<T>::zero());
        first_phase.m_to_optimize.coefs[new_var] = -Constants<T>::one();

#ifdef SIMPLEX_VERBOSE
        cerr << "=== First phase needed\n\n";
        first_phase.print_constraints();
        cerr << "\n";
#endif

        // First step to obtain an admissible solution
        int leaving = -1;
        T val_min;
        for (const Constraint &constr : first_phase.m_constraints) {
            if (leaving == -1 || constr.cst < val_min) {
                val_min = constr.cst;
                leaving = constr.var_index;
            }
        }

        // Execute the first phase of simplex
        first_phase.make_exchange(new_var, leaving);

        Outcome outcome;
        do {
            outcome = first_phase.one_step();
        } while (outcome == NOT_FINISHED);

        // Interpret the results
        assert(outcome == OPTIMAL_SOLUTION);

        if (first_phase.optimal_value() != Constants<T>::zero()) {
            m_outcome = NO_SOLUTION;
            return;
        }

        // The new variable must be non-basic
        for (const Constraint &constr : first_phase.m_constraints) {
            if (constr.var_index == new_var) {
                for (int entering = 0; entering < (int)constr.coefs.size(); entering++) {
                    // We will find such a coefficient
                    if (constr.coefs[entering] != Constants<T>::zero()) {

                        // We can do this exchange as all the variables in the coefficients have a value of zero
                        first_phase.make_exchange(entering, new_var);
                        break;
                    }
                }

                break;
            }
        }

        // Transform the constraints
        m_constraints = first_phase.m_constraints;

        for (Constraint &constr : m_constraints) {
            constr.coefs.pop_back();
        }

        // Fill the function to optimize
        m_to_optimize.var_index = -1;

        m_to_optimize.cst = Constants<T>::zero();
        m_to_optimize.coefs.resize(m_variables_count, Constants<T>::zero());

        for (int var = 0; var < (int)coefs.size(); var++) {
            const T coef = coefs[var];

            bool has_constraint = false;

            // Find the corresponding constraint if it exists
            for (const Constraint &constr : m_constraints) {
                if (constr.var_index == var) {
                    m_to_optimize.cst += coef * constr.cst;
                    for (int var2 = 0; var2 < (int)constr.coefs.size(); var2++) {
                        m_to_optimize.coefs[var2] += coef * constr.coefs[var2];
                    }

                    has_constraint = true;
                    break;
                }
            }

            if (!has_constraint) {
                m_to_optimize.coefs[var] += coef;
            }
        }

#ifdef SIMPLEX_VERBOSE
        cerr << "=== End of the first phase\n\n";
#endif
    } else {
        // Initialize the function to optimize
        m_to_optimize.var_index = -1;
        m_to_optimize.coefs = coefs;
        m_to_optimize.cst = Constants<T>::zero();

        // Add zeros for the new variables to the constraints and the function to
        // optimize
        resize_constraints();
        m_to_optimize.coefs.resize(m_variables_count, Constants<T>::zero());
    }


#ifdef SIMPLEX_VERBOSE
    cerr << "Starting simplex\n\n";
    print_constraints();
    cerr << "\n";
#endif

    do {
        m_outcome = one_step();
    } while (m_outcome == NOT_FINISHED);
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
T Simplex<T>::optimal_value() const
{
    return m_to_optimize.cst;
}

template<class T>
T Simplex<T>::solution_value(const int var) const
{
    for (Constraint constr : m_constraints) {
        if (constr.var_index == var) {
            return constr.cst;
        }
    }

    return Constants<T>::zero();
}

template<class T>
int Simplex<T>::choose_entering_variable() const
{
    for (int i = 0; i < m_variables_count; i++) {
        if (m_to_optimize.coefs[i] > Constants<T>::zero()) {
            return i;
        }
    }

    return -1;
}

template<class T>
int Simplex<T>::choose_leaving_variable(const int entering) const
{
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

    return leaving;
}

template<class T>
void Simplex<T>::make_exchange(const int entering, const int leaving)
{
    // Update the constraints
    int constraint_entering = -1;

    for (int i = 0; i < (int)m_constraints.size(); i++) {
        Constraint &constr = m_constraints[i];

        if (constr.var_index == leaving) {
            const T divider = -constr.coefs[entering];

            constr.coefs[entering] = Constants<T>::zero();
            constr.coefs[leaving] = -Constants<T>::one();

            constr.var_index = entering;

            constr.cst = constr.cst / divider;
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
}

template<class T>
typename Simplex<T>::Outcome Simplex<T>::one_step()
{
    const int entering = choose_entering_variable();
    if (entering == -1) {
        return OPTIMAL_SOLUTION;
    }

    const int leaving = choose_leaving_variable(entering);
    if (leaving == -1) {
        return UNBOUNDED;
    }

    make_exchange(entering, leaving);

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
