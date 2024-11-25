#pragma once

#include <memory>
#include <string>

#include "Graph.h"


class GraphIO {
    static int vertexToIndex(int vertex) {
        return vertex - 1;
    }

    static std::string const filePostfix;
public:
    static std::shared_ptr<Graph> readFromFile(std::string const& fileName);
    static bool writeToFile(std::string const& fileName, std::string const& text);

    static std::shared_ptr<Graph> createRandomGraph(int vertexCount, int edgeCount);
};
