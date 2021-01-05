#ifndef ALGOLIB_HPP
#define ALGOLIB_HPP

#include "global.hpp"

#include "data-structures/MaxHeap.hpp" // ONLY_IF MaxHeap

#include "geometry/Vect2.hpp" // ONLY_IF Vect2
#include "geometry/convex-hull.hpp" // ONLY_IF ConvexHull

#include "graphs/data-structures/Graph.hpp" // ONLY_IF Graph
#include "graphs/data-structures/WGraph.hpp" // ONLY_IF WGraph
#include "graphs/algorithms/BFS.hpp" // ONLY_IF BFS
#include "graphs/algorithms/BellmanFord.hpp" // ONLY_IF BellmanFord
#include "graphs/algorithms/Dijkstra.hpp" // ONLY_IF Dijkstra
#include "graphs/algorithms/edmonds-karp.hpp" // ONLY_IF EdmondsKarp
#include "graphs/algorithms/kosaraju.hpp" // ONLY_IF Kosaraju
#include "graphs/algorithms/min-cut.hpp" // ONLY_IF MinCut
#include "graphs/algorithms/tarjan.hpp" // ONLY_IF Tarjan
#include "graphs/algorithms/TopologicalSort.hpp" // ONLY_IF TopologicalSort
#include "graphs/algorithms/transposeGraph.hpp" // ONLY_IF getTransposeGraph

#include "maths/GCD_LCM.hpp" // ONLY_IF getGCD getLCM getGCDBezout
#include "maths/Permutation.hpp" // ONLY_IF Permutation
#include "maths/Fraction.hpp" // ONLY_IF Fraction
#include "maths/exponentiation_rapide.hpp" // ONLY_IF getPuissance

#include "sorting/merge-sort.hpp" // ONLY_IF mergeSort

#include "2SAT.hpp" // ONLY_IF Resoudre2SAT
#include "infinity.hpp" // ONLY_IF infinity
#include "json.hpp" // ONLY_IF JSON
#include "UnionFind.hpp" // ONLY_IF UnionFind

#endif // ALGOLIB_HPP
