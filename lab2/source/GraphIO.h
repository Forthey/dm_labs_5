#pragma once
#include <memory>

#include "BipartiteGraph.h"


class GraphIO {
public:
    static std::shared_ptr<BipartiteGraph> readGraphFromFile(std::string const &fileName);

    static bool writeResultToFile(std::string const &fileName, Matching const& matching);
};
