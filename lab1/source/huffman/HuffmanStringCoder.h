#pragma once

#include <memory>
#include <unordered_map>

#include "utility/CharCodeWithMeta.h"
#include "utility/BinaryString.h"
#include "utility/BinaryStringReader.h"


class HuffmanStringEncoder {
    BinaryString encoder;
    std::unordered_map<char, CharCodeWithMeta> const& charToCode;
    std::string const& text;

    void encodeCodes();
    void encodeStr();
public:
    HuffmanStringEncoder(std::unordered_map<char, CharCodeWithMeta> const& charToCode, std::string const& text);

    std::shared_ptr<std::string> getEncoded() { return encoder.getString(); };
};

class HuffmanStringDecoder {
    BinaryStringReader reader;
    std::unordered_map<CharCodeWithMeta, char> codeToChar;
    std::shared_ptr<std::string> decoded;

    void decodeCodes();
    void decodeStr();
public:
    explicit HuffmanStringDecoder(std::string const& str);

    std::shared_ptr<std::string> getDecoded() { return decoded; };
};
