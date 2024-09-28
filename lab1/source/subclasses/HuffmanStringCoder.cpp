#include "HuffmanStringCoder.h"

#include <limits>
#include <iostream>

HuffmanStringEncoder::HuffmanStringEncoder(std::unordered_map<char, CharCodeWithMeta> const& charToCode, std::string const& str) :
    charToCode(charToCode), str(str) {
    encodeCodes();
    encodeStr();
}

void HuffmanStringEncoder::encodeCodes() {
    encoded.placeChar(static_cast<char>(charToCode.size()));
    for (auto &[ch, code] : charToCode) {
        encoded.placeChar(ch);
        encoded.placeCharCode({code.length, 6});
        encoded.placeCharCode(code);
    }
}

void HuffmanStringEncoder::encodeStr() {
    for (char const ch : str) {
        encoded.placeCharCode(charToCode.at(ch));
    }
    encoded.setEnd();
}



HuffmanStringDecoder::HuffmanStringDecoder(std::string const& str) : reader(str) {
    decoded = std::make_shared<std::string>();
    decodeCodes();
    decodeStr();
}

void HuffmanStringDecoder::decodeCodes() {
    uint8 codesNumber = reader.next(8);

    for (uint8 i = 0; i < codesNumber; ++i) {
        char ch = char(reader.next(8));
        uint8 codeLength = uint8(reader.next(6));
        uint64 code = reader.next(codeLength);

        codeToChar[code] = ch;
        charToCodeLength[ch] = codeLength;
    }
}

void HuffmanStringDecoder::decodeStr() {
    uint64 code = 0;
    uint8 codeLength = 0;
    while (!reader.reachedEnd()) {
        if (code >= std::numeric_limits<uint64>::max() / 2)
            throw std::runtime_error("ERROR! File is not valid");
        code = (code << 1) + reader.nextBit();
        codeLength++;
        if (codeToChar.contains(code) && charToCodeLength.at(codeToChar.at(code)) == codeLength) {
            *decoded += codeToChar[code];
            code = 0;
            codeLength = 0;
        }
    }

    if (code != 0)
        throw std::runtime_error("ERROR! File is not valid");
}
