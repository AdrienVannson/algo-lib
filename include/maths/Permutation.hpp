#ifndef PERMUTATION_HPP
#define PERMUTATION_HPP

#include "global.hpp"


class Permutation
{
public:
    /// \brief Permutation
    Permutation (const vector<int> &perm);

    /// \brief (a b) transposition of size n
    Permutation (const int n, const int a, const int b);

    inline int size () const
    {
        return m_size;
    }

    inline int operator()  (const int v) const
    {
        if (m_isTransposition) {
            if (v == m_perm[0]) return m_perm[1];
            if (v == m_perm[1]) return m_perm[0];
            return v;
        }

        return m_perm[v];
    }

    vector<int> orbit (const int n) const;
    vector<vector<int>> orbits () const;

    int signature () const;

private:
    int m_size; // Size of the permutation
    bool m_isTransposition;

    // If the permutation is a transposition, contains the two elements that are swapped
    // If not, describes the permutation
    vector<int> m_perm;
};

bool operator== (const Permutation &, const Permutation &);

/// \brief Composition
Permutation operator* (const Permutation &a, const Permutation &b);


#endif // PERMUTATION_HPP
