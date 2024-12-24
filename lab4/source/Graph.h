#pragma once

#include <list>
#include <unordered_set>
#include <vector>


using Vertices = std::vector<int>;
using AdjacencyArray = std::vector<Vertices>;
using Set = std::unordered_set<int>;

class Graph {
    AdjacencyArray vertices;

    bool isStillIndependent(Set const &set, int v) const;

    void traverse(Set &result, Set &graphVertices) const;

public:
    // Класс возвращаемого значения проверки графа
    explicit Graph(AdjacencyArray &&vertices) : vertices(vertices) {}

    std::pair<Set, Set> findLargestIndependentSetAndSmallestCoverage() const;
};
