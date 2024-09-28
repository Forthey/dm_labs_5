#pragma once
#include <memory>
#include "CharCodeWithMeta.h"


class BinaryString {
    std::shared_ptr<std::string> str = std::make_shared<std::string>();
    uint8 bitsAtTheEnd = 0;
public:
    void placeBit(bool const bit);
    void placeChar(char const ch);
    void placeCharCode(CharCodeWithMeta const& code);
    void setEnd();

    std::shared_ptr<std::string> getString();
};
