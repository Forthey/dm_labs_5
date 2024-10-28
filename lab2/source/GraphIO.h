#pragma once
#include <memory>

#include "BipartiteGraph.h"


class GraphIO {
public:
    static std::shared_ptr<BipartiteGraph> readGraphFromFile(std::string const &fileName);

    static std::shared_ptr<BipartiteGraph> writeGraphToFile(std::string const &fileName);
};
