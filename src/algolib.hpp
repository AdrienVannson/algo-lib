#ifndef ALGOLIB_HPP
#define ALGOLIB_HPP

#include "data-structures/DisjointSet.hpp" // ONLY_IF DisjointSet
#include "data-structures/MaxHeap.hpp" // ONLY_IF MaxHeap

#include "geometry/convex-hull.hpp" // ONLY_IF ConvexHull
#include "geometry/intersections.hpp" // ONLY_IF getIntersection
#include "geometry/line.hpp" // ONLY_IF Line
#include "geometry/polygon.hpp" // ONLY_IF Polygon
#include "geometry/projections.hpp" // ONLY_IF getProjection
#include "geometry/segment.hpp" // ONLY_IF Segment
#include "geometry/shape.hpp" // ONLY_IF Shape
#include "geometry/vect2.hpp" // ONLY_IF Vect2
#include "geometry/vect3.hpp" // ONLY_IF Vect3

#include "graphs/algorithms/bellman-ford.hpp" // ONLY_IF BellmanFord
#include "graphs/algorithms/bfs.hpp" // ONLY_IF BFS
#include "graphs/algorithms/dijkstra.hpp" // ONLY_IF Dijkstra
#include "graphs/algorithms/edmonds-karp.hpp" // ONLY_IF EdmondsKarp
#include "graphs/algorithms/floyd-warshall.hpp" // ONLY_IF FloydWarshall
#include "graphs/algorithms/kosaraju.hpp" // ONLY_IF Kosaraju
#include "graphs/algorithms/kruskal.hpp" // ONLY_IF Kruskal
#include "graphs/algorithms/min-cut.hpp" // ONLY_IF MinCut
#include "graphs/algorithms/prim.hpp" // ONLY_IF Prim
#include "graphs/algorithms/tarjan.hpp" // ONLY_IF Tarjan
#include "graphs/algorithms/to-bipartite.hpp" // ONLY_IF ToBipartite
#include "graphs/algorithms/topological-sort.hpp" // ONLY_IF TopologicalSort
#include "graphs/data-structures/Graph.hpp" // ONLY_IF Graph
#include "graphs/data-structures/WGraph.hpp" // ONLY_IF WGraph

#include "maths/Fraction.hpp" // ONLY_IF Fraction
#include "maths/Permutation.hpp" // ONLY_IF Permutation
#include "maths/Polynomial.hpp" // ONLY_IF Polynomial
#include "maths/exponentiation-by-squaring.hpp" // ONLY_IF getPower
#include "maths/gcd-lcm.hpp" // ONLY_IF getGCD getLCM getGCDBezout
#include "maths/matrix.hpp" // ONLY_IF Matrix
#include "maths/modulo.hpp" // ONLY_IF Modulo
#include "maths/prime-decomposition.hpp" // ONLY_IF getPrimeDecomposition
#include "maths/sieve-of-eratosthenes.hpp" // ONLY_IF SieveOfEratosthenes

#include "sorting/merge-sort.hpp" // ONLY_IF mergeSort

#include "strings/automaton.hpp" // ONLY_IF Automaton Aut
#include "strings/kmp.hpp" // ONLY_IF getKmp
#include "strings/regex.hpp" // ONLY_IF Regex Reg
#include "strings/utility/split.hpp" // ONLY_IF split

#include "trees/Tree.hpp" // ONLY_IF Tree
#include "trees/graph-to-forest.hpp" // ONLY_IF graphToForest
#include "trees/graph-to-tree.hpp" // ONLY_IF graphToTree

#include "constants.hpp" // ONLY_IF Constants
#include "json.hpp" // ONLY_IF JSON
#include "two-sat.hpp" // ONLY_IF TwoSat

#endif // ALGOLIB_HPP
