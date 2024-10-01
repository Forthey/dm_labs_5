#pragma once

#include <string>
#include <cstdint>

class BinaryStringReader {
    uint8_t const bitsInChar = 8;

    std::string const &binaryString;
    uint64_t stringIter = 0;
    uint8_t charIter = 0;
public:
    explicit BinaryStringReader(std::string const &binaryString, uint8_t const bitsInChar = 8);

    uint64_t next(uint8_t const numberOfBits);

    bool nextBit();

    bool reachedEnd();
};
