#ifndef AUTOMATON_HPP
#define AUTOMATON_HPP

#include <map>
#include <set>
#include <vector>

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

    // Check string
    bool isAccepted(const std::vector<T> &str) const;

    // Properties and operations
    bool hasEpsilonTransitions() const;
    void removeEpsilonTransitions();


private:
    std::multimap<std::pair<int,T>,int> m_transitions;
    std::multimap<int,int> m_epsilonTransitions;
    std::set<int> m_startStates;
    std::vector<bool> m_isAccepting;
};


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

#endif // AUTOMATON_HPP
