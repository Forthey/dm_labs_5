#pragma once

#include <memory>
#include <unordered_map>

#include "utility/CharCodeWithMeta.h"
#include "utility/StringWithMeta.h"


class HuffmanStringEncoder {
    std::shared_ptr<std::unordered_map<char, CharCodeWithMeta> const> charToCode;
    std::shared_ptr<std::string> encodedTree;
public:
    explicit HuffmanStringEncoder(std::shared_ptr<std::unordered_map<char, CharCodeWithMeta> const> &charToCode)
            : charToCode(charToCode) {}

    StringWithMeta encode(std::string const &str);
};

class HuffmanStringDecoder {
    std::shared_ptr<std::unordered_map<uint64, char> const> codeToChar;
    std::shared_ptr<std::unordered_map<char, uint8> const> charToCodeLength;
public:
    HuffmanStringDecoder(std::shared_ptr<std::unordered_map<uint64 , char>> &codeToChar,
                                  std::shared_ptr<std::unordered_map<char, uint8>> &charToCodeLength
    ) : codeToChar(codeToChar), charToCodeLength(charToCodeLength) {}

    std::shared_ptr<std::string> decode(StringWithMeta const &str);
};
