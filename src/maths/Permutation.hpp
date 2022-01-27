#ifndef PERMUTATION_HPP
#define PERMUTATION_HPP

#include <vector>

class Permutation
{
public:
    /// \brief Permutation
    Permutation(const std::vector<int> &perm);

    /// \brief Identity
    Permutation(const int n);

    /// \brief (a b) transposition of size n
    Permutation(const int n, const int a, const int b);

    inline int size() const { return m_size; }

    inline int operator()(const int v) const
    {
        if (m_isTransposition) {
            if (v == m_perm[0]) return m_perm[1];
            if (v == m_perm[1]) return m_perm[0];
            return v;
        }

        return m_perm[v];
    }

    Permutation inverse() const;

    std::vector<int> orbit(const int n) const;
    std::vector<std::vector<int>> orbits() const;

    int signature() const;

    // Decompositions

    /// \brief Decomposition into composition of transpositions
    std::vector<Permutation> transpositionsDecomposition() const;

private:
    int m_size; // Size of the permutation
    bool m_isTransposition;

    // If the permutation is a transposition, contains the two elements that are swapped
    // If not, describes the permutation
    std::vector<int> m_perm;
};

bool operator==(const Permutation &, const Permutation &);

/// \brief Composition
Permutation operator*(const Permutation &a, const Permutation &b);

#endif // PERMUTATION_HPP
