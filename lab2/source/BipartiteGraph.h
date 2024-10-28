#pragma once
#include <memory>
#include <unordered_set>
#include <utility>

#include "types.h"

using Matching = std::map<int, int>;

class BipartiteGraph {
    Vertices const vertices;
    BipartiteMask mask;
    std::shared_ptr<Matching> matching;

    [[deprecated]] bool findAugChainRec(int const node, bool isFirst = false);

    void findAugChain(int const node);

    void buildMask();
public:
    explicit BipartiteGraph(Vertices vertices_) : vertices(std::move(vertices_)) { buildMask(); };

    std::shared_ptr<Matching> findLargestMatch();
};
