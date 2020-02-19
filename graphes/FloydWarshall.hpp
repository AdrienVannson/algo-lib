#ifndef FLOYDWARSHALL_HPP
#define FLOYDWARSHALL_HPP

#include "../global.hpp"
#include "Graphe.hpp"


class FloydWarshall
{
public:
    FloydWarshall (const Graphe &graphe)
    {
        for (int i=0; i<graphe.nbNoeuds(); i++) {
            m_dists.push_back(vector<int>());
            for (int j=0; j<graphe.nbNoeuds(); j++) {
                if (i == j) {
                    m_dists.back().push_back(0);
                }
                else {
                    m_dists.back().push_back(+oo);
                }
            }
        }

        for (int noeud=0; noeud<graphe.nbNoeuds(); noeud++) {
            for (int iVoisin=0; iVoisin<graphe.nbVoisins(noeud); iVoisin++) {
                const int voisin = graphe.voisin(noeud, iVoisin);
                m_dists[noeud][voisin] = min(m_dists[noeud][voisin], graphe.ponderation(noeud, iVoisin));
            }
        }

        for (int p=0; p<graphe.nbNoeuds(); p++) {
            for (int d=0; d<graphe.nbNoeuds(); d++) {
                for (int f=0; f<graphe.nbNoeuds(); f++) {
                    m_dists[d][f] = min(m_dists[d][p] + m_dists[p][f], m_dists[d][f]);
                }
            }
        }
    }

    int getDist (const int noeud1, const int noeud2) const
    {
        return m_dists[noeud1][noeud2];
    }

private:
    vector<vector<int>> m_dists;
};

#endif // FLOYDWARSHALL_HPP
