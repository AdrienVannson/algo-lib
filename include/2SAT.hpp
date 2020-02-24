#ifndef _2SAT_HPP
#define _2SAT_HPP

#include "graphes/Kosaraju.hpp"

class Resoudre2SAT
{
public:
    Resoudre2SAT (const int nbVariables) :
        m_nbVariables (nbVariables),
        m_grapheContraintes (GRAPHE_ORIENTE, 2*nbVariables)
    {}

    inline int non (const int x) const
    {
        if (x < m_nbVariables) return x + m_nbVariables;
        return x - m_nbVariables;
    }

    /// \brief Ajoute une contrainte de la forme a v b
    void ajouterContrainte (const int a, const int b)
    {
        if (a%m_nbVariables != b%m_nbVariables) {
            m_grapheContraintes.ajouterArc(non(a), b);
            m_grapheContraintes.ajouterArc(non(b), a);
        }
        else if (a == b) {
            m_grapheContraintes.ajouterArc(non(a), a);
        }
    }

    /// \brief Renvoie s'il existe une solution, et calcule une affectation possible
    bool resoudre ()
    {
        Kosaraju kosaraju (m_grapheContraintes); // Calcul des CFC

        m_affectations.clear();

        for (int i=0; i<m_nbVariables; i++) {
            if (kosaraju.CFC(i) == kosaraju.CFC(non(i))) {
                m_affectations.clear();
                return false;
            }
            m_affectations.push_back(kosaraju.CFC(i) > kosaraju.CFC(non(i)));
        }

        return true;
    }

    /// \brief Renvoie l'état auquel la variable peut être affectée pour résoudre le problème
    /// (resoudre doit avoir été appelée auparavant)
    bool estVrai (const int x) const
    {
        return m_affectations[x];
    }


private:
    int m_nbVariables;

    // Représentation d'une variable par un noeud x
    //  - si x < nbVariables : représente x
    //  - si x >= nbVariables : représente non x
    Graphe m_grapheContraintes;

    vector<bool> m_affectations;
};

#endif // _2SAT_HPP
