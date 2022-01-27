#include "Permutation.hpp"

#include <algorithm>
#include <cassert>

using namespace std;

/// \brief Permutation
Permutation::Permutation(const vector<int> &perm) :
    m_size(perm.size()), m_isTransposition(false), m_perm(perm)
{
    vector<bool> isContained(perm.size(), false);

    for (int x : perm) {
        assert(x >= 0 && x < (int)perm.size());
        assert(!isContained[x]);
        isContained[x] = true;
    }
}

/// \brief Identity
Permutation::Permutation(const int n) : m_size(n), m_isTransposition(false), m_perm(n)
{
    for (int i = 0; i < n; i++) {
        m_perm[i] = i;
    }
}

/// \brief (a b) transposition of size n
Permutation::Permutation(const int n, const int a, const int b) :
    m_size(n), m_isTransposition(true), m_perm({a, b})
{
    assert(0 <= a && a < n && 0 <= b && b < n);
    assert(a != b);
}

Permutation Permutation::inverse() const
{
    if (m_isTransposition) return *this;

    vector<int> permInv(size());

    for (int i = 0; i < size(); i++) {
        permInv[m_perm[i]] = i;
    }

    return Permutation(permInv);
}

vector<int> Permutation::orbit(const int n) const
{
    vector<int> ans;

    int x = n;
    do {
        ans.push_back(x);
        x = operator()(x);
    } while (x != n);

    return ans;
}

vector<vector<int>> Permutation::orbits() const
{
    vector<vector<int>> ans;
    vector<bool> isAdded(size(), false);

    for (int i = 0; i < size(); i++) {
        if (!isAdded[i]) {
            ans.push_back({});

            int x = i;
            do {
                ans.back().push_back(x);
                isAdded[x] = true;
                x = operator()(x);
            } while (x != i);
        }
    }

    return ans;
}

int Permutation::signature() const
{
    if (m_isTransposition) return 1;

    vector<bool> isUsed(size(), false);

    int sign = 1;

    for (int i = 0; i < size(); i++) {
        if (!isUsed[i]) {
            int s = 0;

            int x = i;
            do {
                s++;
                isUsed[x] = true;
                x = m_perm[x];
            } while (x != i);

            if (s % 2 == 0) { sign *= -1; }
        }
    }

    return sign;
}

/*
 * Decompositions
 */

/// \brief Decomposition into composition of transpositions
vector<Permutation> Permutation::transpositionsDecomposition() const
{
    if (m_isTransposition) return {*this};

    Permutation perm(m_perm);
    Permutation inv = perm.inverse();

    vector<Permutation> decomposition;

    for (int i = 0; i < (int)perm.size(); i++) {
        const int i2 = perm(i);

        if (i2 != i) {
            decomposition.push_back(Permutation(size(), i, i2));
            swap(perm.m_perm[i], perm.m_perm[inv(i)]);
            swap(inv.m_perm[i], inv.m_perm[i2]);
        }
    }

    return decomposition;
}

bool operator==(const Permutation &a, const Permutation &b)
{
    assert(a.size() == b.size());

    for (int i = 0; i < a.size(); i++) {
        if (a(i) != b(i)) { return false; }
    }

    return true;
}

/// \brief Composition
Permutation operator*(const Permutation &a, const Permutation &b)
{
    assert(a.size() == b.size());

    vector<int> perm;
    for (int i = 0; i < a.size(); i++) {
        perm.push_back(a(b(i)));
    }

    return Permutation(perm);
}
