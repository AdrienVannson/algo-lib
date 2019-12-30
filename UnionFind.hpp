#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP

#include "global.hpp"

template<int NB_NOEUDS>
class UnionFind
{
public:

    UnionFind ()
    {
        for (int iNoeud=0; iNoeud<NB_NOEUDS; iNoeud++) {
            representants[iNoeud] = iNoeud;
            tailles[iNoeud] = 1;
        }
    }

    int representant (const int iNoeud)
    {
        if (representants[iNoeud] == iNoeud) {
            return iNoeud;
        }
        return representants[iNoeud] = representant(representants[iNoeud]);
    }

    int taille (const int iNoeud)
    {
        return tailles[representant(iNoeud)];
    }

    void unir (int iNoeud1, int iNoeud2)
    {
        iNoeud1 = representant(iNoeud1);
        iNoeud2 = representant(iNoeud2);

        if (iNoeud1 == iNoeud2) {
            return;
        }

        if (tailles[iNoeud2] > tailles[iNoeud1]) {
            swap(iNoeud1, iNoeud2);
        }

        tailles[iNoeud1] += tailles[iNoeud2];
        tailles[iNoeud2] = 0;

        representants[iNoeud2] = iNoeud1;
    }

private:
    int representants[NB_NOEUDS];
    int tailles[NB_NOEUDS]; // Valide uniquement pour les racines
};


#endif // UNIONFIND_HPP
