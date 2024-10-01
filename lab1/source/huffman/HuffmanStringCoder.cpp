#include "HuffmanStringCoder.h"

#include <limits>
#include <iostream>

HuffmanStringEncoder::HuffmanStringEncoder(std::unordered_map<char, CharCodeWithMeta> const &charToCode,
                                           std::string const &text) :
        charToCode(charToCode), text(text) {
    encodeCodes();
    encodeStr();
}

void HuffmanStringEncoder::encodeCodes() {
    encoder.placeChar(static_cast<char>(charToCode.size()));
    for (auto &[ch, code]: charToCode) {
        encoder.placeChar(ch);
        encoder.placeCharCode({code.length, 6});
        encoder.placeCharCode(code);
    }
}

void HuffmanStringEncoder::encodeStr() {
    for (char const ch: text) {
        encoder.placeCharCode(charToCode.at(ch));
    }
    encoder.setEnd();
}


HuffmanStringDecoder::HuffmanStringDecoder(std::string const &str) : reader(str) {
    decoded = std::make_shared<std::string>();
    decodeCodes();
    decodeStr();
}

void HuffmanStringDecoder::decodeCodes() {
    uint8 codesNumber = reader.next(8);

    for (uint8 i = 0; i < codesNumber; ++i) {
        char ch = static_cast<char>(reader.next(8));
        uint8 codeLength = static_cast<uint8>(reader.next(6));
        uint64 code = reader.next(codeLength);

        codeToChar[{code, codeLength}] = ch;
    }
}

void HuffmanStringDecoder::decodeStr() {
    uint64 code = 0ull;
    uint8 codeLength = 0;
    while (!reader.reachedEnd()) {
        if (code >= std::numeric_limits<uint64>::max() / 2ull)
            throw std::runtime_error("ERROR! File is not valid");
        code = (code << 1) + reader.nextBit();
        codeLength++;
        if (codeToChar.contains({code, codeLength})) {
            *decoded += codeToChar[{code, codeLength}];
            code = 0ull;
            codeLength = 0;
        }
    }

    if (code != 0ull)
        throw std::runtime_error("ERROR! File is not valid");
}
