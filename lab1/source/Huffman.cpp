#include "Huffman.h"

#include <map>
#include <iostream>
#include <format>

#include "subclasses/HuffmanStringCoder.h"
#include "subclasses/HuffmanIO.h"

namespace Huffman {
    void Huffman::compress(std::string const& text, std::string const& outFilename) {
		auto codes = std::make_shared<HuffmanTree>(text)->buildCodes();
        auto encodedText = std::make_shared<HuffmanStringEncoder>(*codes, text)->getEncoded();

        std::cout << std::format("size: {}B -> {}B ({}%)\n", text.length(), encodedText->length(),
                                 int((1.0 - double(encodedText->length()) / double(text.length())) * 100));

        HuffmanIO::printCodes(codes);
        HuffmanIO::writeToFile(outFilename, *encodedText);
//        auto codeToChar = std::make_shared<std::unordered_map<uint64, char>>();
//        auto charToCodeLength = std::make_shared<std::unordered_map<char, uint8>>();
//        auto decodedText = std::make_shared<HuffmanStringDecoder>(*encodedText)->getDecoded();
	}

    std::shared_ptr<std::string> Huffman::decompress(std::string const& inFilename) {
        return std::make_shared<HuffmanStringDecoder>(*HuffmanIO::readFromFile(inFilename))->getDecoded();
    }
}