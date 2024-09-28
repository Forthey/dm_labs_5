#include "HuffmanStringCoder.h"

StringWithMeta HuffmanStringEncoder::encode(const std::string &str) {
    auto encodedText = std::make_shared<std::string>();

    std::size_t encodedFill = 0ull;

    uint8 i = 0;
    char encodedChunk = char(0);
    for (char const ch : str) {
        CharCodeWithMeta const& code = charToCode->at(ch);
        uint8 discharge = code.length;

        while (discharge > 0) {
            if (i != 0 && i % 8 == 0) {
                encodedText->push_back(encodedChunk);
                encodedChunk = char(0);
                encodedFill++;
            }
            encodedChunk = char(encodedChunk << 1) + ((code.code >> (discharge - uint8(1))) & 1ull);
            discharge--;
            i++;
        }
    }

    if ((i - 1) % 8 != 0) {
        encodedText->push_back(encodedChunk);
    }

    return {encodedText, uint8(i % uint8(8))};
}

std::shared_ptr<std::string> HuffmanStringDecoder::decode(const StringWithMeta &str) {
    auto decodingResult = std::make_shared<std::string>();
    uint64 code = 0ull;
    uint8 codeLength = uint8(0);

    for (std::size_t i = 0ull; i < str.str->length(); ++i) {
        char ch = str.str->at(i);
        uint8 bitsToRead = (i == str.str->length() - 1ull) ? str.bitsAtTheEnd : MAX_BITS_CHUNK;
        uint64 discharge = bitsToRead;

        for (uint8 j = uint8(0); j < bitsToRead; ++j) {
            code = (code << 1) + ((ch >> (discharge - 1)) & 1);
            ++codeLength;
            if (codeToChar->contains(code) && charToCodeLength->at(codeToChar->at(code)) == codeLength) {
                *decodingResult += codeToChar->at(code);
                code = 0ull;
                codeLength = uint8(0);
            }
            discharge--;
        }
    }

    return decodingResult;
}
