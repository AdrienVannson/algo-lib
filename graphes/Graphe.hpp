#ifndef GRAPHE_HPP
#define GRAPHE_HPP

#include "../global.hpp"

// Propriétés du graphe (TODO: ne pas utiliser de int, car on peut échanger propriétés et nbNoeuds dans le constructeur)
const int GRAPHE_ORIENTE = 1<<0;
const int GRAPHE_NON_ORIENTE = 0;
const int GRAPHE_PONDERE = 1<<1;
const int GRAPHE_NON_PONDERE = 0;


class Graphe
{
public:
    Graphe (const int proprietes, const int nbNoeuds=0) :
        m_proprietes (proprietes),
        m_nbArcs (0)
    {
        m_noeuds.resize(nbNoeuds);
    }

    void lire (const bool doitDecrementer=false)
    {
        int nbNoeuds, nbArcs;
        cin >> nbNoeuds >> nbArcs;
        m_noeuds.resize(nbNoeuds);

        for (int i=0; i<nbArcs; i++) {
            int noeud1, noeud2;
            int ponderation = 1;

            cin >> noeud1 >> noeud2;
            if (m_proprietes & GRAPHE_PONDERE) cin >> ponderation;

            if (doitDecrementer) noeud1--, noeud2--;

            if (m_proprietes & GRAPHE_ORIENTE) {
                ajouterArc(noeud1, noeud2, ponderation);
            }
            else {
                ajouterArrete(noeud1, noeud2, ponderation);
            }
        }
    }


    inline int nbNoeuds () const
    {
        return m_noeuds.size();
    }

    inline int nbVoisins (const int noeud) const
    {
        return m_noeuds[noeud].size();
    }

    inline int voisin (const int noeud, const int iVoisin) const
    {
        return m_noeuds[noeud][iVoisin].first;
    }

    inline int idArc (const int noeud, const int iVoisin) const
    {
        return m_noeuds[noeud][iVoisin].second;
    }

    inline int idArcVers (const int noeud, const int voisin)
    {
        for (int arc=0; arc<nbVoisins(noeud); arc++) {
            if (m_noeuds[noeud][arc].first == voisin) {
                return m_noeuds[noeud][arc].second;
            }
        }
        return -1;
    }

    inline int ponderation (const int noeud, const int iVoisin) const
    {
        return m_ponderations[ m_noeuds[noeud][iVoisin].second ];
    }
    inline void setPonderation (const int arc, const int ponderation)
    {
        m_ponderations[arc] = ponderation;
    }
    inline void setPonderation (const int noeud, const int iVoisin, const int ponderation)
    {
        m_ponderations[ m_noeuds[noeud][iVoisin].second ] = ponderation;
    }

    inline const vector<pair<int,int>>& arcs (const int noeud) const
    {
        return m_noeuds[noeud];
    }


    inline void ajouterArc (const int noeud1, const int noeud2, const int ponderation=1)
    {
        m_noeuds[noeud1].push_back(make_pair(noeud2, m_nbArcs++));
        if (m_proprietes & GRAPHE_PONDERE) m_ponderations.push_back(ponderation);
    }

    inline void ajouterArrete (const int noeud1, const int noeud2, const int ponderation=1)
    {
        m_noeuds[noeud1].push_back(make_pair(noeud2, m_nbArcs));
        m_noeuds[noeud2].push_back(make_pair(noeud1, m_nbArcs++));
        if (m_proprietes & GRAPHE_PONDERE) m_ponderations.push_back(ponderation);
    }

private:
    int m_proprietes;
    int m_nbArcs;
    vector<vector<pair<int, int>>> m_noeuds; // [noeud][voisin] --> {idVoisin, idArc}
    vector<int> m_ponderations;
};

#endif // GRAPHE_HPP
