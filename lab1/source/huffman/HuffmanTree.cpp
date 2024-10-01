#include <stack>
#include <queue>
#include <iostream>
#include <format>
#include <utility>

#include "HuffmanTree.h"


HuffmanTree::HuffmanTree(char character, std::size_t freq) {
    root = std::make_shared<Node>(
            Node{character, freq, nullptr, nullptr}
    );
}

HuffmanTree::HuffmanTree(HuffmanTree &left, HuffmanTree &right) {
    root = std::make_shared<Node>(0, left.root->freq + right.root->freq, left.root, right.root);
}

HuffmanTree::HuffmanTree(const std::string &text) {
    root = buildHuffmanTree(countCharacters(text))->root;
}


std::unordered_map<char, CharCodeWithMeta> HuffmanTree::buildCodes() {
    class TraversingData {
    public:
        std::shared_ptr<Node> node = nullptr;
        CharCodeWithMeta const nodeCode = {0ull, 0};

        TraversingData(
                std::shared_ptr<Node> const& node, CharCodeWithMeta const& nodeCode
                ) : node(node), nodeCode(nodeCode) {}
    };
    std::unordered_map<char, CharCodeWithMeta> codes;

    // If text contains only 1 character
    if (!root->left & !root->right) {
        codes.insert({root->character, {1ull, static_cast<uint8_t>(1)}});
        return codes;
    }

    std::stack<TraversingData> stack;
    stack.push({root, {0ull, static_cast<uint8_t>(0)}});

    while (!stack.empty()) {
        TraversingData data = stack.top();
        stack.pop();

        if (!data.node->left && !data.node->right) {
            codes.emplace(data.node->character, data.nodeCode);
            continue;
        }

        stack.push({
            data.node->left, {
                data.nodeCode.code << 1, static_cast<uint8_t>(data.nodeCode.length + uint8_t(1))
            }
        });
        stack.push({
            data.node->right, {
                (data.nodeCode.code << 1) + 1, static_cast<uint8_t>(data.nodeCode.length + uint8_t(1))
            }
        });
    }

    return codes;
}

std::unordered_map<char, std::size_t> HuffmanTree::countCharacters(const std::string &text) {
    std::unordered_map<char, std::size_t> charFrequency;

    for (char const &ch: text) {
        if (!charFrequency.contains(ch))
            charFrequency.emplace(ch, 1ull);
        else
            charFrequency.at(ch)++;
    }

    return charFrequency;
}

std::shared_ptr<HuffmanTree> HuffmanTree::buildHuffmanTree(const std::unordered_map<char, std::size_t> &characterFreq) {
    class compareTrees
    {
    public:
        bool operator()(std::shared_ptr<HuffmanTree> const& left, std::shared_ptr<HuffmanTree> const& right){
            return left->root->freq > right->root->freq;
        }
    };

    std::priority_queue<std::shared_ptr<HuffmanTree>, std::vector<std::shared_ptr<HuffmanTree>>, compareTrees> symbolsQueue;

    for (auto const &[ch, freq]: characterFreq) {
        symbolsQueue.emplace(std::make_shared<HuffmanTree>(ch, freq));
    }

    while (symbolsQueue.size() > 1ull) {
        auto tree1 = symbolsQueue.top();
        symbolsQueue.pop();
        auto tree2 = symbolsQueue.top();
        symbolsQueue.pop();

        symbolsQueue.emplace(std::make_shared<HuffmanTree>(*tree1, *tree2));
    }

    return symbolsQueue.top();
}
