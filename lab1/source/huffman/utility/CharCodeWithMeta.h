#pragma once

class CharCodeWithMeta {
public:
    uint64_t code;
    uint8_t length;

    bool operator==(CharCodeWithMeta const &code) const {
        return this->code == code.code && length == code.length;
    }
};

template<>
struct std::hash<CharCodeWithMeta> {
    std::size_t operator()(const CharCodeWithMeta &key) const {
        return key.code >= key.length ? key.code * key.code + key.code + key.length : key.code +
                                                                                      key.length * key.length;
    }
};