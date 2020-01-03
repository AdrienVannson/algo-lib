#ifndef KOSARAJU_HPP
#define KOSARAJU_HPP

#include "../global.hpp"
#include "Graphe.hpp"
#include "inverserArcs.hpp"

// Calcule les composantes fortement connexes d'un graphe orienté
class Kosaraju
{
public:
    Kosaraju (const Graphe &graphe) :
        m_nbCFCs (0)
    {
        m_CFCs.resize(graphe.nbNoeuds());
        m_estVu.resize(graphe.nbNoeuds(), false);

        for (int i=0; i<graphe.nbNoeuds(); i++) calculerOrdreParcours(graphe, i);

        fill(m_estVu.begin(), m_estVu.end(), false);
        const Graphe grapheInverse = inverserArcs(graphe);

        for (int i=m_aVisiter.size()-1; i>=0; i--) {
            const int noeud = m_aVisiter[i];
            if (!m_estVu[noeud]) {
                ajouterDansCFC(grapheInverse, noeud, m_nbCFCs);
                m_nbCFCs++;
            }
        }
    }

    int nbCFCs () const
    {
        return m_nbCFCs;
    }

    int CFC (const int noeud) const
    {
        return m_CFCs[noeud];
    }


private:
    void calculerOrdreParcours (const Graphe &g, const int noeud)
    {
        if (m_estVu[noeud]) return;
        m_estVu[noeud] = true;

        for (int i=0; i<g.nbVoisins(noeud); i++) {
            calculerOrdreParcours(g, g.voisin(noeud, i));
        }

        m_aVisiter.push_back(noeud);
    }

    void ajouterDansCFC (const Graphe &g, const int noeud, const int idCFC)
    {
        if (m_estVu[noeud]) return;
        m_estVu[noeud] = true;

        m_CFCs[noeud] = idCFC;

        for (int i=0; i<g.nbVoisins(noeud); i++) {
            ajouterDansCFC(g, g.voisin(noeud, i), idCFC);
        }
    }

    vector<int> m_aVisiter;
    vector<bool> m_estVu;

    int m_nbCFCs;
    vector<int> m_CFCs;
};

#endif // KOSARAJU_HPP
