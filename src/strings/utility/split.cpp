#include "split.hpp"

using namespace std;

vector<string> split(const string &str, const vector<char> &separators)
{
    vector<string> res;
    string current;

    for (const char c : str) {
        bool isSeparator = false;
        for (char sep : separators) {
            if (c == sep) isSeparator = true;
        }

        if (isSeparator) {
            if (current.size()) {
                res.push_back(current);
                current.clear();
            }
        } else {
            current.push_back(c);
        }
    }

    if (current.size()) {
        res.push_back(current);
    }

    return res;
}

vector<string> split(const string &str, const char sep)
{
    return split(str, vector<char> {sep});
}
