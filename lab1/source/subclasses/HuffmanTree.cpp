#include <stack>
#include <queue>

#include "HuffmanTree.h"


HuffmanTree::HuffmanTree(char character, std::size_t freq) {
    root = std::make_shared<Node>(
            Node{character, freq, nullptr, nullptr}
    );
}

HuffmanTree::HuffmanTree(HuffmanTree &&left, HuffmanTree &&right) {
    root = std::make_shared<Node>(
            Node{0, left.root->freq + right.root->freq, left.root, right.root}
    );
}

HuffmanTree::HuffmanTree(const std::string &text) : HuffmanTree(*buildHuffmanTree(*countCharacters(text))) {
}


std::size_t HuffmanTree::getRootFreq() const { return root->freq; }

std::shared_ptr<std::unordered_map<char, CharCodeWithMeta> const> HuffmanTree::buildCodes() {
    class TraverseData {
    public:
        std::shared_ptr<HuffmanTree::Node> node = nullptr;
        CharCodeWithMeta nodeCode = {0, 0};
    };

    std::stack<TraverseData> stack;
    auto codes = std::make_shared<std::unordered_map<char, CharCodeWithMeta>>();

    stack.push({root, {}});

    while (!stack.empty()) {
        TraverseData data = stack.top();
        stack.pop();

        if (!data.node->left && !data.node->right) {
            codes->insert({data.node->character, data.nodeCode});
            continue;
        }

        if (data.node != root)
            data.nodeCode.code <<= 1;
        ++data.nodeCode.length;
        stack.push({data.node->left, data.nodeCode});
        data.nodeCode.code++;
        stack.push({data.node->right, data.nodeCode});
    }

    return codes;
}

std::shared_ptr<std::unordered_map<char, std::size_t> const> HuffmanTree::countCharacters(const std::string &text) {
    auto charFrequency = std::make_shared<std::unordered_map<char, std::size_t>>();

    for (char const &ch: text) {
        if (charFrequency->find(ch) == charFrequency->end())
            charFrequency->insert({ch, 0});
        else
            charFrequency->at(ch)++;
    }

    return charFrequency;
}

std::shared_ptr<HuffmanTree> HuffmanTree::buildHuffmanTree(const std::unordered_map<char, std::size_t> &characterFreq) {
    std::priority_queue<std::shared_ptr<HuffmanTree>, std::vector<std::shared_ptr<HuffmanTree>>, std::greater<>> symbolsQueue;

    for (auto const &[ch, freq]: characterFreq) {
        symbolsQueue.emplace(std::make_shared<HuffmanTree>(ch, freq));
    }

    while (symbolsQueue.size() > 1ull) {
        std::shared_ptr<HuffmanTree> tree1 = symbolsQueue.top();
        symbolsQueue.pop();
        std::shared_ptr<HuffmanTree> tree2 = symbolsQueue.top();
        symbolsQueue.pop();

        symbolsQueue.emplace(std::make_shared<HuffmanTree>(std::move(*tree1), std::move(*tree2)));
    }

    return symbolsQueue.top();
}

