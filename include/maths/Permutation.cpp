#include "Permutation.hpp"

Permutation::Permutation (const vector<int> &perm) :
    m_perm (perm)
{
    vector<bool> isContained (perm.size(), false);

    for (int x : perm) {
        assert(x >= 0 && x < (int)perm.size());
        assert(!isContained[x]);
        isContained[x] = true;
    }
}

vector<int> Permutation::orbit (const int n) const
{
    vector<int> ans;

    int x = n;
    do {
        ans.push_back(x);
        x = m_perm[x];
    } while (x != n);

    return ans;
}

vector<vector<int>> Permutation::orbits () const
{
    vector<vector<int>> ans;
    vector<bool> isAdded (m_perm.size(), false);

    for (int i=0; i<size(); i++) {
        if (!isAdded[i]) {
            ans.push_back({});

            int x = i;
            do {
                ans.back().push_back(x);
                isAdded[x] = true;
                x = m_perm[x];
            } while (x != i);
        }
    }

    return ans;
}

int Permutation::signature () const
{
    vector<bool> isUsed (m_perm.size(), false);

    int sign = 1;

    for (int i=0; i<size(); i++) {
        if (!isUsed[i]) {
            int s = 0;

            int x = i;
            do {
                s++;
                isUsed[x] = true;
                x = m_perm[x];
            } while (x != i);

            if (s % 2 == 0) {
                sign *= -1;
            }
        }
    }

    return sign;
}

bool operator== (const Permutation &a, const Permutation &b)
{
    assert(a.size() == b.size());

    for (int i=0; i<a.size(); i++) {
        if (a(i) != b(i)) {
            return false;
        }
    }

    return true;
}

// Composition
Permutation operator* (const Permutation &a, const Permutation &b)
{
    assert(a.size() == b.size());

    vector<int> perm;
    for (int x=0; x<a.size(); x++) {
        perm.push_back( a(b(x)) );
    }

    return Permutation (perm);
}
