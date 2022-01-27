#ifndef KMP_HPP
#define KMP_HPP

#include <algorithm>
#include <string>
#include <vector>

template<class C>
std::vector<int> getKmp(const std::vector<C> &S)
{
    std::vector<int> l;
    l.push_back(-1);

    for (int k = 1; k <= (int)S.size(); k++) {
        int t = l.back();
        while (t != -1 && S[t] != S[k - 1]) {
            t = l[t];
        }
        l.push_back(t + 1);
    }

    return l;
}

std::vector<int> getKmp(const std::string &s)
{
    std::vector<char> v(s.size());
    std::copy(s.begin(), s.end(), v.begin());
    return getKmp(v);
}

#endif // KMP_HPP
