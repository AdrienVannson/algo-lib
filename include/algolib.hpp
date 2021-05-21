#ifndef ALGOLIB_HPP
#define ALGOLIB_HPP

#include "data-structures/DisjointSet.hpp" // ONLY_IF DisjointSet
#include "data-structures/MaxHeap.hpp" // ONLY_IF MaxHeap

#include "geometry/Vect2.hpp" // ONLY_IF Vect2
#include "geometry/convex-hull.hpp" // ONLY_IF ConvexHull

#include "graphs/data-structures/Graph.hpp" // ONLY_IF Graph
#include "graphs/data-structures/WGraph.hpp" // ONLY_IF WGraph
#include "graphs/algorithms/bfs.hpp" // ONLY_IF BFS
#include "graphs/algorithms/bellman-ford.hpp" // ONLY_IF BellmanFord
#include "graphs/algorithms/dijkstra.hpp" // ONLY_IF Dijkstra
#include "graphs/algorithms/edmonds-karp.hpp" // ONLY_IF EdmondsKarp
#include "graphs/algorithms/floyd-warshall.hpp" // ONLY_IF FloydWarshall
#include "graphs/algorithms/kosaraju.hpp" // ONLY_IF Kosaraju
#include "graphs/algorithms/kruskal.hpp" // ONLY_IF Kruskal
#include "graphs/algorithms/min-cut.hpp" // ONLY_IF MinCut
#include "graphs/algorithms/prim.hpp" // ONLY_IF Prim
#include "graphs/algorithms/tarjan.hpp" // ONLY_IF Tarjan
#include "graphs/algorithms/topological-sort.hpp" // ONLY_IF TopologicalSort
#include "graphs/algorithms/transpose-graph.hpp" // ONLY_IF getTransposeGraph

#include "maths/exponentiation-by-squaring.hpp" // ONLY_IF getPower
#include "maths/GCD_LCM.hpp" // ONLY_IF getGCD getLCM getGCDBezout
#include "maths/Permutation.hpp" // ONLY_IF Permutation
#include "maths/Polynomial.hpp" // ONLY_IF Polynomial
#include "maths/Fraction.hpp" // ONLY_IF Fraction

#include "sorting/merge-sort.hpp" // ONLY_IF mergeSort

#include "2SAT.hpp" // ONLY_IF Resoudre2SAT
#include "strings/kmp.hpp" // ONLY_IF getKmp
#include "strings/regex.hpp" // ONLY_IF Regex

#include "constants.hpp" // ONLY_IF Constants
#include "json.hpp" // ONLY_IF JSON

#endif // ALGOLIB_HPP
