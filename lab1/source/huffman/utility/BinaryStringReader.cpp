#include "BinaryStringReader.h"

#include <iostream>
#include <format>

BinaryStringReader::BinaryStringReader(std::string const &binaryString, uint8_t const bitsInChar) : binaryString(
        binaryString), bitsInChar(bitsInChar) {
    if (binaryString.length() < 2)
        throw std::runtime_error(std::format("Invalid binary string length: too short ({})", binaryString.length()));
}

uint64_t BinaryStringReader::next(uint8_t const numberOfBits) {
    uint64_t result = 0;
    for (uint8_t i = 0; i < numberOfBits; ++i)
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

