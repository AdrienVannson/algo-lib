#ifndef TWO_SAT_HPP
#define TWO_SAT_HPP

#include <vector>

#include "graphs/algorithms/kosaraju.hpp"
#include "graphs/data-structures/Graph.hpp"

class TwoSat
{
public:
    TwoSat(const int variableCount) :
        m_variableCount(variableCount),
        m_constraintGraph(2 * variableCount, true)
    {}

    /// \brief Returns the negation of a variable.
    inline int negation(const int x) const
    {
        if (x < m_variableCount) return x + m_variableCount;
        return x - m_variableCount;
    }

    /// \brief Alias for negation
    inline int neg(const int x) const
    {
        return negation(x);
    }

    /// \brief Add the constraint (x v y)
    void addConstraint(const int x, const int y)
    {
        if (x % m_variableCount != y % m_variableCount) {
            m_constraintGraph.addEdge(neg(x), y);
            m_constraintGraph.addEdge(neg(y), x);
        } else if (x == y) {
            m_constraintGraph.addEdge(neg(x), x);
        }
    }

    /// \brief Add the constraint (x)
    void addConstraint(const int x)
    {
        addConstraint(x, x);
    }

    /// \brief Tries to solve the 2-SAT instance, and returns if a solution
    /// exists.
    bool solve()
    {
        assert(m_affectations.empty());

        // Strongly connected components
        Kosaraju<Graph> kosaraju(m_constraintGraph);

        for (int x = 0; x < m_variableCount; x++) {
            if (kosaraju.scc(x) == kosaraju.scc(neg(x))) {
                m_affectations.clear();
                return false;
            }

            m_affectations.push_back(kosaraju.scc(x) > kosaraju.scc(neg(x)));
        }

        return true;
    }

    /// \brief If a solution exists, returns a possible value for the variable
    /// (the solve function must have been called beforehand).
    bool isTrue(const int x) const
    {
        assert(m_affectations.size());
        return m_affectations[x];
    }

private:
    int m_variableCount;

    // The vertex s represents:
    //  - the litteral s                       if s < m_variableCount
    //  - the litteral (not s-m_variableCount) otherwise
    Graph m_constraintGraph;

    std::vector<bool> m_affectations;
};

#endif // TWO_SAT_HPP
