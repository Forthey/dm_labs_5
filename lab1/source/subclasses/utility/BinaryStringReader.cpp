#include "BinaryStringReader.h"

#include <iostream>
#include <format>

BinaryStringReader::BinaryStringReader(std::string const& binaryString) : binaryString(binaryString) {
    if (binaryString.length() < 2)
        throw std::runtime_error(std::format("Invalid binary string length: too short ({})", binaryString.length()));
}

uint64 BinaryStringReader::next(uint8 const numberOfBits) {
    uint64 result = 0;
    for (uint8 i = 0; i < numberOfBits; ++i)
        result = (result << 1) + nextBit();
    return result;
}

bool BinaryStringReader::nextBit() {
    if (stringIter == binaryString.length() - 2 && charIter >= binaryString.back())
        throw std::runtime_error("ERROR! Unexpected EOF");

    bool result = (binaryString[stringIter] >> (7 - charIter)) & 1;
    charIter = (charIter + 1) % 8;
    if (charIter == 0)
        stringIter++;

    return result;
}

bool BinaryStringReader::reachedEnd() {
    return stringIter == binaryString.length() - 2 && charIter >= binaryString.back();
}

