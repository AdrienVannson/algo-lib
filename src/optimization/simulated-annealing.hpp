#pragma once

template<typename S>
class SimulatedAnnealing {
public:
    SimulatedAnnealing(const double startTemperature):
        m_startTemperature(startTemperature)
    {}

    void minimize(const S startState, const int nbIterations) {
        m_state = startState;
        m_bestState = startState;
        m_score = m_state.score();
        m_bestScore = m_score;

        for (int i = 0; i < nbIterations; i++) {
            const double temperature = m_startTemperature * (1 - i / (double)nbIterations);

            const S neighbor = m_state.randomNeighbor();
            const double newScore = neighbor.score();

            const double delta = newScore - m_score;
            
            if (delta < 0 || (rand() / (double)RAND_MAX) < exp(-delta / temperature)) {
                m_state = neighbor;
                m_score = newScore;
            }

            if (m_score < m_bestScore) {
                m_bestState = m_state;
                m_bestScore = m_score;
            }
        }
    }

    double m_startTemperature;

    // Current and best solutions
    S m_state, m_bestState;
    double m_score, m_bestScore;
};
