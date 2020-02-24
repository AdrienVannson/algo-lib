#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "../global.hpp"
#include "Graphe.hpp"


class Dijkstra
{
public:
    Dijkstra (const Graphe &graphe, const int depart)
    {
        m_dists.resize(graphe.nbNoeuds(), +oo);

        priority_queue<pair<int, int>> aVoir; // {-dist, noeud}
        aVoir.push(make_pair(0, depart));

        while (aVoir.size()) {
            const int noeud = aVoir.top().second;
            const int dist = -aVoir.top().first;
            aVoir.pop();

            if (m_dists[noeud] != +oo) {
                continue;
            }
            m_dists[noeud] = dist;

            for (int iVoisin=0; iVoisin<graphe.nbVoisins(noeud); iVoisin++) {
                const int voisin = graphe.voisin(noeud, iVoisin);

                if (m_dists[voisin] == +oo) {
                    aVoir.push(make_pair(-dist-graphe.ponderation(noeud, iVoisin), voisin));
                }
            }
        }
    }

    int getDist (const int noeud) const
    {
        return m_dists[noeud];
    }

private:
    vector<int> m_dists;
};

#endif // DIJKSTRA_HPP
