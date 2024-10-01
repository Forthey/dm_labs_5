#pragma once

#include <memory>
#include "CharCodeWithMeta.h"


class BinaryString {
    uint8_t const bitsInChar = 8;

    std::shared_ptr<std::string> str = std::make_shared<std::string>();
    uint8_t bitsAtTheEnd = 0;
public:
    BinaryString(uint8_t const bitsInChar = 8) : bitsInChar(bitsInChar) {}

    void placeBit(bool const bit);

    void placeChar(char const ch);

    void placeCharCode(CharCodeWithMeta const &code);

    void setEnd();

    std::shared_ptr<std::string> getString();
};
