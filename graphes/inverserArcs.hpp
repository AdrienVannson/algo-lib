#ifndef INVERSERARCS_HPP
#define INVERSERARCS_HPP

#include "Graphe.hpp"

Graphe inverserArcs (const Graphe &graphe)
{
    Graphe nouveauGraphe (GRAPHE_ORIENTE, graphe.nbNoeuds());
    for (int noeud=0; noeud<graphe.nbNoeuds(); noeud++) {
        for (int iVoisin=0; iVoisin<graphe.nbVoisins(noeud); iVoisin++) {
            nouveauGraphe.ajouterArc(graphe.voisin(noeud, iVoisin), noeud);
        }
    }
    return nouveauGraphe;
}

#endif // INVERSERARCS_HPP
