#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP

#include "global.hpp"


class UnionFind
{
public:

    UnionFind (const int nbNoeuds)
    {
        representants.reserve(nbNoeuds);

        for (int iNoeud=0; iNoeud<nbNoeuds; iNoeud++) {
            representants.push_back(iNoeud);
        }

        tailles.resize(nbNoeuds, 1);
    }

    int representant (const int iNoeud)
    {
        if (representants[iNoeud] == iNoeud) {
            return iNoeud;
        }
        return representants[iNoeud] = representant(representants[iNoeud]);
    }

    /// \brief Renvoie la taille de la composante dans laquelle se trouve le noeud
    int taille (const int iNoeud)
    {
        return tailles[representant(iNoeud)];
    }

    /// \brief Fusionne deux composantes
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
    vector<int> representants;
    vector<int> tailles; // Valide uniquement pour les racines
};


#endif // UNIONFIND_HPP
