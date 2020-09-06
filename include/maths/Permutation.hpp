#ifndef PERMUTATION_HPP
#define PERMUTATION_HPP

#include "global.hpp"


class Permutation
{
public:
    Permutation (const vector<int> &perm);

    inline int size () const
    {
        return m_perm.size();
    }

    inline int operator()  (const int v) const
    {
        return m_perm[v];
    }

    vector<int> orbit (const int n) const;
    vector<vector<int>> orbits () const;

    int signature () const;

private:
    vector<int> m_perm;
};

bool operator== (const Permutation &, const Permutation &);

// Composition
Permutation operator* (const Permutation &a, const Permutation &b);


#endif // PERMUTATION_HPP
