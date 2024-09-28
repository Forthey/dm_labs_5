#pragma once
#include <string>
#include <memory>

#include "types.h"


#define MAX_BITS_CHUNK 8
#define MAX_CHUNK_DISCHARGE (1ull << (MAX_BITS_CHUNK - 1))

class StringWithMeta {
public:
    std::shared_ptr<std::string> str;
    uint8 bitsAtTheEnd;
};