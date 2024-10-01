#include "BinaryStringReader.h"

#include <iostream>
#include <format>

BinaryStringReader::BinaryStringReader(std::string const &binaryString, uint8 const bitsInChar) : binaryString(
        binaryString), bitsInChar(bitsInChar) {
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

    if (charIter == bitsInChar) {
        charIter = 0;
        stringIter++;
    }
    bool result = (binaryString[stringIter] >> (bitsInChar - 1 - charIter)) & 1;
    charIter++;

    return result;
}

bool BinaryStringReader::reachedEnd() {
    return stringIter == binaryString.length() - 2 && charIter >= binaryString.back();
}

