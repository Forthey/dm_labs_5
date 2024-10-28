#include "BipartiteGraph.h"

#include <algorithm>
#include <list>
#include <ranges>
#include <stack>


bool BipartiteGraph::findAugChainRec(int const node, bool const isFirst) {
    static std::vector<bool> visited;

    if (isFirst) visited.resize(vertices.size(), false);

    if (visited[node]) {
        return false;
    }
    visited[node] = true;

    for (auto &rightNode: vertices.at(node)) {
        if (!matching->contains(rightNode) || findAugChainRec(matching->at(rightNode))) {
            matching->emplace(rightNode, node);
            return true;
        }
    }
    return false;
}

void BipartiteGraph::findAugChain(int const node) {
    struct NodeChain {
        struct NodePair {
            int right;
            int left;
        };

        int node;
        std::list<NodePair> nodePair;
    };

    std::stack<NodeChain> stack;
    std::vector<bool> visited(vertices.size(), false);

    stack.push({node});

    while (!stack.empty()) {
        NodeChain nodeChain = stack.top();
        stack.pop();

        if (visited[nodeChain.node]) {
            continue;
        }
        visited[nodeChain.node] = true;

        for (auto &rightNode: vertices.at(nodeChain.node)) {
            if (!matching->contains(rightNode)) {
                for (auto& [right, left] : nodeChain.nodePair) {
                    (*matching)[right] = left;
                }
                matching->emplace(rightNode, nodeChain.node);
                break;
            }

            NodeChain newChain = nodeChain;
            newChain.nodePair.emplace_back(rightNode, nodeChain.node);
            newChain.node = matching->at(rightNode);
            stack.emplace(std::move(newChain));
        }
    }
}

void BipartiteGraph::buildMask() {
    if (vertices.empty())
        return;

    std::queue<int> bfsQueue;

    int node = vertices.begin()->first;
    bfsQueue.push(node);
    mask[node] = true;

    while (!bfsQueue.empty()) {
        node = bfsQueue.front();
        bfsQueue.pop();

        for (auto &rightNode: vertices.at(node)) {
            if (mask.contains(rightNode)) {
                continue;
            }
            mask[rightNode] = !mask[node];
            bfsQueue.push(rightNode);
        }
    }
}

std::shared_ptr<Matching> BipartiteGraph::findLargestMatch() {
    matching = std::make_shared<Matching>();

    for (auto &node: std::views::keys(vertices)) {
        if (!mask[node])
            continue;
        findAugChain(node);
    }
    return matching;
}
