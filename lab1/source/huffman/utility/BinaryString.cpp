#include <iostream>
#include "BinaryString.h"

void BinaryString::placeBit(bool const bit) {
    char cBit = static_cast<char>(bit);
    if (bitsAtTheEnd % bitsInChar == 0) {
        str->push_back(cBit);
        bitsAtTheEnd = 1;
        return;
    }
    str->back() = static_cast<char>(str->back() << 1) + cBit;
    bitsAtTheEnd++;
}

void BinaryString::placeChar(char const ch) {
    for (uint8_t i = bitsInChar; i > 0; --i)
        placeBit((ch >> (i - 1)) & 1);
}

void BinaryString::placeCharCode(CharCodeWithMeta const &code) {
    for (uint8_t i = code.length; i > 0; --i) {
        placeBit((code.code >> (i - 1)) & 1);
    }
}

std::shared_ptr<std::string> BinaryString::getString() {
    return str;
}

void BinaryString::setEnd() {
    uint8_t trueBitsAtTheEnd = bitsAtTheEnd;
    while (bitsAtTheEnd != bitsInChar) {
        placeBit(0);
    }
    placeCharCode({trueBitsAtTheEnd, bitsInChar});
}
