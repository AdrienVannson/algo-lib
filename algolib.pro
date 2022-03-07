TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
        #src/2SAT.hpp \
        src/algolib.hpp \
        src/constants.hpp \
        src/data-structures/DisjointSet.hpp \
        src/data-structures/MaxHeap.hpp \
        src/geometry/Vect2.hpp \
        src/geometry/convex-hull.hpp \
        src/graphs/algorithms/bellman-ford.hpp \
        src/graphs/algorithms/bfs.hpp \
        src/graphs/algorithms/dijkstra.hpp \
        src/graphs/algorithms/edmonds-karp.hpp \
        src/graphs/algorithms/floyd-warshall.hpp \
        src/graphs/algorithms/kosaraju.hpp \
        src/graphs/algorithms/kruskal.hpp \
        src/graphs/algorithms/min-cut.hpp \
        src/graphs/algorithms/prim.hpp \
        src/graphs/algorithms/tarjan.hpp \
        src/graphs/algorithms/to-bipartite.hpp \
        src/graphs/algorithms/topological-sort.hpp \
        src/graphs/algorithms/transpose-graph.hpp \
        src/graphs/data-structures/Graph.hpp \
        src/graphs/data-structures/WGraph.hpp \
        src/json.hpp \
        src/maths/GCD_LCM.hpp \
        src/maths/Permutation.hpp \
        src/maths/Fraction.hpp \
        src/global.hpp \
        src/maths/Polynomial.hpp \
        src/maths/exponentiation-by-squaring.hpp \
        src/sorting/merge-sort.hpp \
        src/strings/automaton.hpp \
        src/strings/kmp.hpp \
        src/strings/regex.hpp \
        src/trees/Tree.hpp \
        src/trees/graph-to-tree.hpp

SOURCES += \
    src/json.cpp \
    src/maths/Permutation.cpp \
    src/trees/Tree.cpp \
    tests/main.cpp

INCLUDEPATH += src
