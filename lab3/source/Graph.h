#pragma once

#include <list>
#include <vector>

using Cycle = std::vector<int>;
using Path = std::pmr::list<int>;
using Vertices = std::vector<std::vector<int> >;
using ConnectivityComponents = std::vector<std::vector<int> >;

class Graph {
    Vertices vertices;

    static Cycle extractCycleFromPath(int vertex, Path const &path);
    static Cycle extractCycleFromPath(Path const &path);
    int countEdges() const;
    std::pair<ConnectivityComponents, Cycle> checkIfAcyclicAndConnected();
public:
    // Класс возвращаемого значения проверки графа
    struct CheckResult {
        ConnectivityComponents const connectivity_components;
        Cycle const cycle;
        int const edgeCnt;
        int const vertexCnt;

        CheckResult(ConnectivityComponents &&connectivity_components, Cycle &&cycle,
                    const int edgesCnt, const int vertexCnt) : connectivity_components(connectivity_components),
                                          cycle(cycle), edgeCnt(edgesCnt), vertexCnt(vertexCnt) {
        }
    };

    explicit Graph(Vertices &&vertices) : vertices(vertices) {}

    CheckResult checkTreeProperties();
};
