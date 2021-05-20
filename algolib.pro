TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
        include/2SAT.hpp \
        include/algolib.hpp \
        include/constants.hpp \
        include/data-structures/DisjointSet.hpp \
        include/data-structures/MaxHeap.hpp \
        include/geometry/Vect2.hpp \
        include/geometry/convex-hull.hpp \
        include/graphs/algorithms/bellman-ford.hpp \
        include/graphs/algorithms/bfs.hpp \
        include/graphs/algorithms/dijkstra.hpp \
        include/graphs/algorithms/edmonds-karp.hpp \
        include/graphs/algorithms/floyd-warshall.hpp \
        include/graphs/algorithms/kosaraju.hpp \
        include/graphs/algorithms/kruskal.hpp \
        include/graphs/algorithms/min-cut.hpp \
        include/graphs/algorithms/prim.hpp \
        include/graphs/algorithms/tarjan.hpp \
        include/graphs/algorithms/topological-sort.hpp \
        include/graphs/algorithms/transpose-graph.hpp \
        include/graphs/data-structures/Graph.hpp \
        include/graphs/data-structures/WGraph.hpp \
        include/json.hpp \
        include/maths/GCD_LCM.hpp \
        include/maths/Permutation.hpp \
        include/maths/Fraction.hpp \
        include/global.hpp \
        include/maths/Polynomial.hpp \
        include/maths/exponentiation-by-squaring.hpp \
        include/sorting/merge-sort.hpp \
        include/strings/kmp.hpp \
        include/strings/regex.hpp

SOURCES += \
    include/json.cpp \
    include/maths/Permutation.cpp \
    tests/main.cpp

INCLUDEPATH += include
