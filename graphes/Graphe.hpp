#ifndef GRAPHE_HPP
#define GRAPHE_HPP

#include "../global.hpp"

class Graphe
{
public:
    Graphe (const int nbNoeuds=0) :
        m_nbArcs (0)
    {
        m_noeuds.resize(nbNoeuds);
    }

    void lire (const bool estOriente, const bool doitDecrementer=false)
    {
        int nbNoeuds, nbArcs;
        cin >> nbNoeuds >> nbArcs;
        m_noeuds.resize(nbNoeuds);

        for (int i=0; i<nbArcs; i++) {
            int noeud1, noeud2;
            cin >> noeud1 >> noeud2;

            if (doitDecrementer) noeud1--, noeud2--;

            if (estOriente) {
                ajouterArc(noeud1, noeud2);
            }
            else {
                ajouterArrete(noeud1, noeud2);
            }

        }
    }

    void reset ()
    {
        m_nbArcs = 0;
        m_noeuds.clear();
    }

    // Lecture
    inline int nbNoeuds () const { return m_noeuds.size(); }
    inline int nbVoisins (const int noeud) const { return m_noeuds[noeud].size(); }

    inline int voisin (const int noeud, const int voisin) const { return m_noeuds[noeud][voisin].first; }
    inline const vector<pair<int,int>>& arcs (const int noeud) const { return m_noeuds[noeud]; }

    // Modification
    inline void ajouterArc (const int noeud1, const int noeud2)
    {
        m_noeuds[noeud1].push_back(make_pair(noeud2, m_nbArcs++));
    }
    inline void ajouterArrete (const int noeud1, const int noeud2)
    {
        m_noeuds[noeud1].push_back(make_pair(noeud2, m_nbArcs++));
        m_noeuds[noeud2].push_back(make_pair(noeud1, m_nbArcs++));
    }

private:
    int m_nbArcs;
    vector<vector<pair<int, int>>> m_noeuds; // [noeud][voisin] --> {idVoisin, idArc}
};

#endif // GRAPHE_HPP
