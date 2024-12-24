#include "GraphIO.h"

#include <fstream>
#include <iostream>
#include <random>

std::string const GraphIO::filePostfix = ".graph";

std::shared_ptr<Graph> GraphIO::readFromFile(std::string const &fileName) {
    std::ifstream f(fileName + filePostfix);
    if (!f.is_open()) {
        return nullptr;
    }

    int vertexCount;
    if (!(f >> vertexCount)) {
        return nullptr;
    }

    AdjacencyArray vertices(vertexCount);

    for (int i = 0; i < vertexCount; i++) {
        int vertex, edgeCount;
        if (!(f >> vertex >> edgeCount)) {
            return nullptr;
        }

        vertices[vertexToIndex(vertex)].resize(edgeCount);
        for (int j = 0; j < edgeCount; j++) {
            int adjVertex;
            if (!(f >> adjVertex)) {
                return nullptr;
            }
            vertices[vertexToIndex(vertex)][j] = vertexToIndex(adjVertex);
        }
    }

    return std::make_shared<Graph>(std::move(vertices));
}

bool GraphIO::writeToFile(std::string const &fileName, Set const &largestSet, Set const& minCoverage) {
    std::ofstream f(fileName + filePostfix + ".out");
    if (!f.is_open()) {
        return false;
    }

    std::string textResult = "Наибольшее независимое множество вершин:\n\t- ";
    for (int v : largestSet) {
        textResult += std::to_string(v + 1) + " ";
    }
    textResult += "\n\nНаименьшее вершинное покрытие:\n\t- ";
    for (int v : minCoverage) {
        textResult += std::to_string(v + 1) + " ";
    }
    textResult += "\n";

    std::cout << textResult;

    f << textResult;

    return true;
}

std::shared_ptr<Graph> GraphIO::createRandomGraph(int vertexCount, int edgeCount) {
    if (vertexCount <= 0 || edgeCount < 0) {
        return nullptr;
    }
    AdjacencyArray vertices(vertexCount);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> getRandomVertex(0, vertexCount - 1);
    for (int i = 0; i < edgeCount; i++) {
        std::uint8_t u = getRandomVertex(rng);
        std::uint8_t v = getRandomVertex(rng);

        // vertices[u].emplace_back(v);
        // if (u != v) {
        //     vertices[v].emplace_back(u);
        // }
    }

    return std::make_shared<Graph>(std::move(vertices));
}
