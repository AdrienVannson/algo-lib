TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
        include/2SAT.hpp \
        include/algolib.hpp \
        include/data-structures/DisjointSet.hpp \
        include/data-structures/MaxHeap.hpp \
        include/geometry/Vect2.hpp \
        include/geometry/convex-hull.hpp \
        include/graphes/BFS.hpp \
        include/graphes/Dijkstra.hpp \
        include/graphs/algorithms/BFS.hpp \
        include/graphs/algorithms/BellmanFord.hpp \
        include/graphs/algorithms/Dijkstra.hpp \
        include/graphs/algorithms/TopologicalSort.hpp \
        include/graphs/algorithms/edmonds-karp.hpp \
        include/graphs/algorithms/floyd-warshall.hpp \
        include/graphs/algorithms/kosaraju.hpp \
        include/graphs/algorithms/kruskal.hpp \
        include/graphs/algorithms/min-cut.hpp \
        include/graphs/algorithms/tarjan.hpp \
        include/graphs/algorithms/transposeGraph.hpp \
        include/graphs/data-structures/Graph.hpp \
        include/graphs/data-structures/WGraph.hpp \
        include/infinity.hpp \
        include/json.hpp \
        include/maths/GCD_LCM.hpp \
        include/maths/Permutation.hpp \
        include/maths/exponentiation_rapide.hpp \
        include/graphes/Graphe.hpp \
        include/maths/Fraction.hpp \
        include/global.hpp \
        include/sorting/merge-sort.hpp

SOURCES += \
    include/json.cpp \
    include/maths/Permutation.cpp \
    tests/main.cpp

INCLUDEPATH += include
