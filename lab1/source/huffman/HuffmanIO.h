#pragma once

#include <memory>
#include <unordered_map>
#include <iostream>

#include "utility/CharCodeWithMeta.h"


class HuffmanIO {
    static std::string prettyCode(CharCodeWithMeta const &code);

    static std::string prettySize(uint64_t size);

public:
    static void printCodes(std::unordered_map<char, CharCodeWithMeta> const& codes,
                           std::ostream &out = std::cout);

    static void printStats(uint64_t const sizeBefore, uint64_t const sizeAfter);

    static void saveStats(uint64_t const size, uint64_t const compressedSize);

    static void writeToFile(std::string const &filename, std::string const &str);

    static std::shared_ptr<std::string const> readFromFile(std::string const &filename);
};