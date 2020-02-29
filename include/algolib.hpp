#ifndef ALGOLIB_HPP
#define ALGOLIB_HPP

#include "global.hpp"

#include "graphs/data-structures/Graph.hpp" // ONLY_IF Graph
#include "graphs/data-structures/WGraph.hpp" // ONLY_IF WGraph
#include "graphs/algorithms/BFS.hpp" // ONLY_IF BFS
#include "graphs/algorithms/BellmanFord.hpp" // ONLY_IF BellmanFord
#include "graphs/algorithms/Dijkstra.hpp" // ONLY_IF Dijkstra
#include "graphs/algorithms/TopologicalSort.hpp" // ONLY_IF TopologicalSort
#include "graphs/algorithms/transposeGraph.hpp" // ONLY_IF getTransposeGraph

#include "2SAT.hpp" // ONLY_IF Resoudre2SAT

#include "UnionFind.hpp" // ONLY_IF UnionFind

#include "maths/PGCD_PPCM.hpp" // ONLY_IF PGCD PPCM PGCD_bezout
#include "maths/Fraction.hpp" // ONLY_IF Fraction
#include "maths/exponentiation_rapide.hpp" // ONLY_IF getPuissance


#endif // ALGOLIB_HPP
