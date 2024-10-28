#include "GraphIO.h"

#include <format>
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

    Vertices vertices(verticesCnt + 1);

    for (int i = 0; i < verticesCnt; i++) {
        int node;
        if (!(f >> node)) {
            return nullptr;
        }
        std::vector<int> adjNodes;
        while (f.peek() != '\n') {
            int adjNode;
            if (!(f >> adjNode)) {
                return nullptr;
            }
            adjNodes.emplace_back(adjNode);
        }
        vertices[node] = std::move(adjNodes);
    }

    return std::make_shared<BipartiteGraph>(vertices);
}

bool GraphIO::writeResultToFile(std::string const &fileName, Matching const &matching) {
    std::ofstream f(fileName);
    if (!f.is_open()) {
        return false;
    }

    f << std::format("{}\n", matching.size());
    for (auto &[left, right]: matching) {
        f << std::format("{} {}\n", left, right);
    }

    return true;
}
