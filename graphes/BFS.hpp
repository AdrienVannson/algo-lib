#ifndef BFS_HPP
#define BFS_HPP

#include "../global.hpp"
#include "Graphe.hpp"


class BFS
{
public:
    BFS (const Graphe &graphe, const int depart)
    {
        for (int noeud=0; noeud<graphe.nbNoeuds(); noeud++) {
            if (noeud == depart) {
                m_dists.push_back(0);
            }
            else {
                m_dists.push_back(+oo);
            }
        }

        queue<pair<int, int>> aVoir; // {noeud, dist}
        aVoir.push(make_pair(depart, 0));

        while (aVoir.size()) {
            const int noeud = aVoir.front().first;
            const int dist = aVoir.front().second;
            aVoir.pop();

            for (int iVoisin=0; iVoisin<graphe.nbVoisins(noeud); iVoisin++) {
                const int voisin = graphe.voisin(noeud, iVoisin);

                if (m_dists[voisin] == +oo) {
                    m_dists[voisin] = dist + 1;
                    aVoir.push(make_pair(voisin, dist+1));
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

#endif // BFS_HPP
