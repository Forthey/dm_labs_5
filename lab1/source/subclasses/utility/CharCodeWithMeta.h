#pragma once
#include "types.h"

#define MAX_CODE_LENGTH static_cast<uint8>(64)

class CharCodeWithMeta {
public:
    uint64 code;
    uint8 length;
};
