#pragma once

#include <memory>
#include <unordered_map>

#include "utility/CharCodeWithMeta.h"


class HuffmanTree {
    static std::shared_ptr<std::unordered_map<char, std::size_t> const> countCharacters(std::string const &text);

    static std::shared_ptr<HuffmanTree> buildHuffmanTree(std::unordered_map<char, std::size_t> const &characterFreq);

public:
    class Node {
    public:
        char character;
        std::size_t freq;

        std::shared_ptr<Node> left, right;

        auto operator<=>(Node const &node) const { return freq > node.freq; };
    };

    std::shared_ptr<Node> root = nullptr;

    explicit HuffmanTree(std::string const &text);

    HuffmanTree(char character, std::size_t freq);

    HuffmanTree(HuffmanTree &&left, HuffmanTree &&right);

    [[nodiscard]] std::size_t getRootFreq() const;

    [[nodiscard]] std::shared_ptr<std::unordered_map<char, CharCodeWithMeta> const> buildCodes();

    auto operator<=>(HuffmanTree const &tree) const { return root > tree.root; };
};


