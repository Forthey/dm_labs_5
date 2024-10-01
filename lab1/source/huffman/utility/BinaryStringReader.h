#pragma once

#include <string>

#include "types.h"


class BinaryStringReader {
    uint8 const bitsInChar = 8;

    std::string const &binaryString;
    uint64 stringIter = 0;
    uint8 charIter = 0;
public:
    explicit BinaryStringReader(std::string const &binaryString, uint8 const bitsInChar = 8);

    uint64 next(uint8 const numberOfBits);

    bool nextBit();

    bool reachedEnd();
};
