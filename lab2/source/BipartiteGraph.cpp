#include "BipartiteGraph.h"

#include <algorithm>
#include <list>
#include <queue>
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

inline bool visited(int const lastVisited, int const node) {
    return lastVisited >= node;
}

void BipartiteGraph::findAugChain(int const node) {
    struct NodeChain {
        struct NodePair {
            int right;
            int left;
        };

        int node;
        int adjNodesIndex = 0;
        std::list<NodePair> nodePair;
    };

    std::stack<NodeChain> stack;
    int lastVisitedNode = -1;

    stack.push({node});

    while (!stack.empty()) {
        NodeChain& nodeChain = stack.top();
        if ((nodeChain.adjNodesIndex == 0 && visited(lastVisitedNode, nodeChain.node)) || nodeChain.adjNodesIndex >= vertices.at(nodeChain.node).size()) {
            stack.pop();
            continue;
        }
        lastVisitedNode = nodeChain.node;

        if (auto& adjNodes = vertices.at(nodeChain.node); nodeChain.adjNodesIndex < adjNodes.size()) {
            int rightNode = adjNodes[nodeChain.adjNodesIndex];
            nodeChain.adjNodesIndex++;
            if (!matching->contains(rightNode)) {
                for (auto& [right, left] : nodeChain.nodePair) {
                    (*matching)[right] = left;
                }
                matching->emplace(rightNode, nodeChain.node);
                stack.pop();
            } else {
                NodeChain newChain = nodeChain;
                newChain.nodePair.emplace_back(rightNode, nodeChain.node);
                newChain.node = matching->at(rightNode);
                stack.emplace(std::move(newChain));
            }
        }
    }
}

void BipartiteGraph::buildMask() {
    if (vertices.size() <= 1)
        return;

    std::queue<int> bfsQueue;
    int node = 1;
    bfsQueue.push(node);
    mask[node] = true;

    while (!bfsQueue.empty()) {
        node = bfsQueue.front();
        bfsQueue.pop();

        for (auto &rightNode: vertices.at(node)) {
            if (mask[rightNode]) {
                continue;
            }
            mask[rightNode] = !mask[node];
            bfsQueue.push(rightNode);
        }
    }
}

std::shared_ptr<Matching> BipartiteGraph::findLargestMatch() {
    matching = std::make_shared<Matching>();

    for (int node = 1; node < vertices.size(); node++) {
        if (!mask[node])
            continue;
        findAugChain(node);
    }
    return matching;
}
