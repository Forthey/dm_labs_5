#include "GraphIO.h"

#include <fstream>


std::shared_ptr<BipartiteGraph> GraphIO::readGraphFromFile(std::string const &fileName) {
    std::ifstream f(fileName);

    if (!f.is_open()) {
        return nullptr;
    }

    int verticesCnt;

    if (!(f >> verticesCnt)) {
        return nullptr;
    }

    Vertices vertices;

    for (int i = 0; i < verticesCnt; i++) {
        int node;
        if (!(f >> node)) {
            return nullptr;
        }
        std::set<int> adjNodes;
        while (f.peek() != '\n') {
            int adjNode;
            if (!(f >> adjNode)) {
                return nullptr;
            }
            adjNodes.emplace(adjNode);
        }
        vertices[node] = std::move(adjNodes);
    }

    return std::make_shared<BipartiteGraph>(vertices);
}
