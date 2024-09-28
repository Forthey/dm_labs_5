#include <iostream>
#include "BinaryString.h"

void BinaryString::placeBit(bool const bit) {
    char cBit = char(bit);
    if (bitsAtTheEnd % 8 == 0) {
        str->push_back(char(bit));
        bitsAtTheEnd = 1;
        return;
    }
    str->back() = char(str->back() << 1) + cBit;
    bitsAtTheEnd++;
}

void BinaryString::placeChar(char const ch) {
    for (uint8 i = 8; i > 0; --i)
        placeBit((ch >> (i - 1)) & 1);
}

void BinaryString::placeCharCode(CharCodeWithMeta const& code) {
    for (uint8 i = code.length; i > 0; --i) {
        placeBit((code.code >> (i - 1)) & 1);
    }
}

std::shared_ptr<std::string> BinaryString::getString() {
    return str;
}

void BinaryString::setEnd() {
    uint8 trueBitsAtTheEnd = bitsAtTheEnd != 0 ? bitsAtTheEnd : 8;
    while (bitsAtTheEnd != 8) {
        placeBit(0);
    }
    placeCharCode({trueBitsAtTheEnd, 8});
}
