#pragma once

#include <memory>
#include <unordered_map>
#include <iostream>

#include "utility/CharCodeWithMeta.h"


class HuffmanIO {
    static std::shared_ptr<std::string> prettyCode(CharCodeWithMeta const &code);

public:
    class ReturnInfo {
    public:
        std::shared_ptr<std::unordered_map<uint64, char>> codeToChar;
        std::shared_ptr<std::unordered_map<char, uint8>> charToCodeLength;
        std::shared_ptr<std::string const> encodedStr;
    };

    static void printCodes(std::shared_ptr<std::unordered_map<char, CharCodeWithMeta> const> const &codes,
                    std::ostream &out = std::cout);

    static void writeToFile(std::string const &filename, std::string const &str);
    static std::shared_ptr<std::string const> readFromFile(std::string const &filename);
};