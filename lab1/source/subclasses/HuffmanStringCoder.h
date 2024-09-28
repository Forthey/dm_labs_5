#pragma once

#include <memory>
#include <unordered_map>

#include "utility/CharCodeWithMeta.h"
#include "utility/BinaryString.h"
#include "utility/BinaryStringReader.h"


class HuffmanStringEncoder {
    BinaryString encoded;
    std::unordered_map<char, CharCodeWithMeta> const& charToCode;
    std::string const& str;

    void encodeCodes();
    void encodeStr();
public:
    HuffmanStringEncoder(std::unordered_map<char, CharCodeWithMeta> const& charToCode, std::string const& str);

    std::shared_ptr<std::string> getEncoded() { return encoded.getString(); };
};

class HuffmanStringDecoder {
    std::unordered_map<uint64 , char> codeToChar;
    std::unordered_map<char, uint8> charToCodeLength;
    BinaryStringReader reader;
    std::shared_ptr<std::string> decoded;

    void decodeCodes();
    void decodeStr();
public:
    explicit HuffmanStringDecoder(std::string const& str);

    std::shared_ptr<std::string> getDecoded() { return decoded; };
};
