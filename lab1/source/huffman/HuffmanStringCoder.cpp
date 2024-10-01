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
    encoder.placeChar(static_cast<char>(charToCode.size() - 1ull));
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
    uint8_t codesNumber = reader.next(8);

    for (uint16_t i = 0; i <= codesNumber; ++i) {
        char ch = static_cast<char>(reader.next(8));
        uint8_t codeLength = static_cast<uint8_t>(reader.next(6));
        uint64_t code = reader.next(codeLength);

        codeToChar[{code, codeLength}] = ch;
    }
}

void HuffmanStringDecoder::decodeStr() {
    uint64_t code = 0ull;
    uint8_t codeLength = 0;
    while (!reader.reachedEnd()) {
        if (code >= std::numeric_limits<uint64_t>::max() / 2ull)
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
