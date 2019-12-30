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
        nbCFCs (0)
    {
        CFCs.resize(graphe.nbNoeuds());
        estVu.resize(graphe.nbNoeuds(), false);

        for (int i=0; i<graphe.nbNoeuds(); i++) calculerOrdreParcours(graphe, i);

        fill(estVu.begin(), estVu.end(), false);
        const Graphe grapheInverse = inverserArcs(graphe);

        for (int i=aVisiter.size()-1; i>=0; i--) {
            const int noeud = aVisiter[i];
            if (!estVu[noeud]) {
                ajouterDansCFC(grapheInverse, noeud, nbCFCs);
                nbCFCs++;
            }
        }
    }

    int nbCFCs;
    vector<int> CFCs;

private:
    void calculerOrdreParcours (const Graphe &g, const int noeud)
    {
        if (estVu[noeud]) return;
        estVu[noeud] = true;

        for (int i=0; i<g.nbVoisins(noeud); i++) {
            calculerOrdreParcours(g, g.voisin(noeud, i));
        }

        aVisiter.push_back(noeud);
    }

    void ajouterDansCFC (const Graphe &g, const int noeud, const int idCFC)
    {
        if (estVu[noeud]) return;
        estVu[noeud] = true;

        CFCs[noeud] = idCFC;

        for (int i=0; i<g.nbVoisins(noeud); i++) {
            ajouterDansCFC(g, g.voisin(noeud, i), idCFC);
        }
    }

    vector<int> aVisiter;
    vector<bool> estVu;
};

#endif // KOSARAJU_HPP
