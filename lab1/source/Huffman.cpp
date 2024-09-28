#include "Huffman.h"

#include <map>
#include <iostream>
#include <format>

#include "subclasses/HuffmanStringCoder.h"

namespace Huffman {
    void Huffman::compress(std::string const& text) {
		auto huffmanTree = std::make_shared<HuffmanTree>(text);
		auto codes = huffmanTree->buildCodes();
        auto encodedText = std::make_shared<HuffmanStringEncoder>(codes)->encode(text);

        std::cout << "length: " << encodedText.str->length() << " - " << int(encodedText.bitsAtTheEnd) << "bits at the end" << std::endl;
        std::cout << "encoding result: " << *encodedText.str << "\n";
        for (auto ch : *encodedText.str) {
            std::cout << std::format("{}\n", std::to_string(ch));
        }
//        printCodes(codes);

        auto codeToChar = std::make_shared<std::unordered_map<uint64, char>>();
        auto charToCodeLength = std::make_shared<std::unordered_map<char, uint8>>();
        for (auto const& [ch, code] : *codes) {
            codeToChar->insert({code.code, ch});
            charToCodeLength->insert({ch, code.length});
        }
        auto decodedText = std::make_shared<HuffmanStringDecoder>(codeToChar, charToCodeLength)->decode(encodedText);
        std::cout << *decodedText << std::endl;
	}

}