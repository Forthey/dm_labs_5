#pragma once

#include <memory>
#include <unordered_map>

#include "utility/CharCodeWithMeta.h"
#include "utility/StringWithMeta.h"


class HuffmanIO {
    std::shared_ptr<std::string> prettyCode(CharCodeWithMeta const &code);

public:
    class ReturnInfo {
    public:
        std::shared_ptr<std::unordered_map<uint64, char>> codeToChar;
        std::shared_ptr<std::unordered_map<char, uint8>> charToCodeLength;
        std::shared_ptr<std::string const> encodedStr;
    };

    void printCodes(std::shared_ptr<std::unordered_map<char, CharCodeWithMeta> const> const &codes,
                    std::ostream &out = std::cout);

    void writeToFile(std::string const &filename, std::string const &str);

    std::shared_ptr<std::string const> readFromFile(std::string const &filename);

    void writeToFileEncoded(std::string const &filename,
                            std::shared_ptr<std::unordered_map<char, CharCodeWithMeta> const> &codes,
                            StringWithMeta const &encodedText);

    ReturnInfo readFromFileEncoded(std::string const &filename);
};