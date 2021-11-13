#ifndef AUTOMATON_HPP
#define AUTOMATON_HPP

#include <algorithm>
#include <map>
#include <set>
#include <vector>

#include "regex.hpp"

// T: type of the letters
template<class T>
class Automaton
{
public:
    Automaton();

    // Structure of the automaton
    int stateCount() const;
    void addState(const bool isStart, const bool isAccepting);

    void addEpsilonTransition(const int state1, const int state2);
    void addTransition(const int state1, const T letter, const int state2);

    std::vector<T> alphabet() const;

    void clear();

    // Check string
    bool isAccepted(const std::vector<T> &str) const;

    // Properties and operations
    bool hasEpsilonTransitions() const;
    void removeEpsilonTransitions();


    // Closure properties
    void applyKleenStar();
    void applyKleenPlus();

    void operator+=(const Automaton<T> &other);
    void operator*=(const Automaton<T> &other); // Concatenation

    template<class U>
    friend Automaton<U> operator+(const Automaton<U> &a, const Automaton<U> &b);

    template<class U>
    friend Automaton<U> operator*(const Automaton<U> &a, const Automaton<U> &b);

    // Regex
    static Automaton<T> fromRegex(const Regex<T> *r);
    // Printing
    template<class U>
    friend std::ostream &operator<<(std::ostream &os, const Automaton<U> &aut);

private:
    std::multimap<std::pair<int,T>,int> m_transitions;
    std::multimap<int,int> m_epsilonTransitions;
    std::set<int> m_startStates;
    std::vector<bool> m_isAccepting;
};

using Aut = Automaton<char>;


template<class T>
Automaton<T>::Automaton()
{}


/*
 * Structure of the automaton
 */

template<class T>
int Automaton<T>::stateCount() const
{
    return m_isAccepting.size();
}

template<class T>
void Automaton<T>::addState(const bool isStart, const bool isAccepting)
{
    m_isAccepting.push_back(isAccepting);

    if (isStart) {
        m_startStates.insert(m_isAccepting.size() - 1);
    }
}

template<class T>
void Automaton<T>::addEpsilonTransition(const int state1, const int state2)
{
    m_epsilonTransitions.insert(std::make_pair(state1, state2));
}

template<class T>
void Automaton<T>::addTransition(const int state1, const T letter, const int state2)
{
    m_transitions.insert(std::make_pair(
        std::make_pair(state1, letter),
        state2
    ));
}

template<class T>
std::vector<T> Automaton<T>::alphabet() const
{
    std::set<T> set;
    for (const auto &transition : m_transitions) {
        set.insert(transition.first.second);
    }

    std::vector<T> res;
    for (T c : set) {
        res.push_back(c);
    }
    return res;
}

template<class T>
void Automaton<T>::clear()
{
    m_transitions.clear();
    m_epsilonTransitions.clear();
    m_startStates.clear();
    m_isAccepting.clear();
}


/*
 * Check string
 */

template<class T>
bool Automaton<T>::isAccepted(const std::vector<T> &str) const
{
    assert(!hasEpsilonTransitions());

    std::set<int> states = m_startStates;

    for (const T c : str) {
        std::set<int> nextStates;

        for (int state : states) {
            auto range = m_transitions.equal_range(std::make_pair(state, c));

            for (auto it=range.first; it!=range.second; it++) {
                nextStates.insert(it->second);
            }
        }

        states.swap(nextStates);
    }

    for (int state : states) {
        if (m_isAccepting[state]) {
            return true;
        }
    }
    return false;
}


/*
 * Properties and operations
 */

template<class T>
bool Automaton<T>::hasEpsilonTransitions() const
{
    return m_epsilonTransitions.size() > 0;
}

/*
 * Closure properties
 */

template<class T>
void Automaton<T>::applyKleenStar()
{
    if (m_startStates.empty()) {
        clear();
        addState(true, true);
        return;
    }

    addState(true, true);

    for (int s : m_startStates) {
        if (s != stateCount() - 1) {
            addEpsilonTransition(stateCount() - 1, s);
        }
    }

    m_startStates.clear();
    m_startStates.insert(stateCount() - 1);
}

template<class T>
void Automaton<T>::applyKleenPlus()
{
    for (int s1=0; s1<stateCount(); s1++) {
        if (!m_isAccepting[s1]) continue;

        for (int s2 : m_startStates) {
            if (s1 != s2) {
                m_epsilonTransitions.insert(std::make_pair(s1, s2));
            }
        }
    }
}

template<class T>
void Automaton<T>::operator+=(const Automaton<T> &other)
{
    const int n = stateCount();

    // Add states
    for (int s = 0; s < other.stateCount(); s++) {
        const auto it = other.m_startStates.find(s);
        const bool isStart = it != other.m_startStates.end();

        addState(isStart, other.m_isAccepting[s]);
    }

    // Add transitions
    for (const std::pair<std::pair<int,T>,int> trans : other.m_transitions) {
        addTransition(n + trans.first.first, trans.first.second, n + trans.second);
    }

    // Add epsilon-transitions
    for (const std::pair<int,int> trans : other.m_epsilonTransitions) {
        addEpsilonTransition(n + trans.first, n + trans.second);
    }
}

template<class T>
void Automaton<T>::operator*=(const Automaton<T> &other)
{
    const int n = stateCount();

    const std::vector<bool> prevIsAccepting = m_isAccepting;
    std::fill(m_isAccepting.begin(), m_isAccepting.end(), false);

    // Add states
    for (int s = 0; s < other.stateCount(); s++) {
        addState(false, other.m_isAccepting[s]);
    }

    // Add transitions
    for (const std::pair<std::pair<int,T>,int> trans : other.m_transitions) {
        addTransition(n + trans.first.first, trans.first.second, n + trans.second);
    }

    // Add epsilon-transitions
    for (const std::pair<int,int> trans : other.m_epsilonTransitions) {
        addEpsilonTransition(n + trans.first, n + trans.second);
    }

    // Link the two automatons
    for (int s1 = 0; s1 < n; s1++) {
        if (!prevIsAccepting[s1]) continue;

        for (int s2 : other.m_startStates) {
            addEpsilonTransition(s1, n + s2);
        }
    }
}

template<class T>
Automaton<T> operator+(const Automaton<T> &a, const Automaton<T> &b)
{
    Automaton<T> res = a;
    res += b;
    return res;
}

template<class T>
Automaton<T> operator*(const Automaton<T> &a, const Automaton<T> &b)
{
    Automaton<T> res = a;
    res *= b;
    return res;
}


/*
 * Regex
 */

template<class T>
Automaton<T> Automaton<T>::fromRegex(const Regex<T> *r)
{
    Automaton<T> aut;

    switch (r->type()) {
    case Regex<T>::EMPTY_SET:
        return aut;

    case Regex<T>::EMPTY_STRING:
        aut.addState(true, true);
        return aut;

    case Regex<T>::CHARACTER:
        aut.addState(true, false);
        aut.addState(false, true);
        aut.addTransition(0, r->character(), 1);
        return aut;

    case Regex<T>::CONCATENATION:
        return fromRegex(r->regex1()) * fromRegex(r->regex2());

    case Regex<T>::ALTERNATION:
        return fromRegex(r->regex1()) + fromRegex(r->regex2());

    case Regex<T>::KLEEN_STAR:
        aut = fromRegex(r->regex1());
        aut.applyKleenStar();
        return aut;
    }

    assert(false);
}


/*
 * Printing
 */

template<class T>
std::ostream &operator<<(std::ostream &os, const Automaton<T> &aut)
{
    os << "Automaton :\n";

    os << " | Start states :";
    for (int s : aut.m_startStates) {
        os << " " << s;
    }
    os << "\n";

    for (int s = 0; s < (int)aut.stateCount(); s++) {
        os << " | State " << s << " (";
        if (!aut.m_isAccepting[s]) {
            os << "not ";
        }
        os << "accepting) :";

        // Transitions
        for (std::pair<std::pair<int,T>,int> trans : aut.m_transitions) {
            if (trans.first.first == s) {
                os << " [" << trans.first.second << " -> " << trans.second << "]";
            }
        }

        // Epsilon-transitions
        auto range = aut.m_epsilonTransitions.equal_range(s);

        for (auto it=range.first; it!=range.second; it++) {
            os << " [ɛ -> " << it->second << "]";
        }

        os << "\n";
    }


    return os;
}

#endif // AUTOMATON_HPP
