#include "Huffman.h"

#include <iostream>
#include <format>

#include "huffman/HuffmanTree.h"
#include "huffman/HuffmanStringCoder.h"
#include "huffman/HuffmanIO.h"

namespace Huffman {
    std::unordered_map<Huffman::KwargsKeys, bool> const Huffman::defaultKwargs = {
            {KwargsKeys::print_codes, false},
            {KwargsKeys::print_stats, true},
            {KwargsKeys::save_stats, false},
    };


    void Huffman::compress(std::string const &inFilename, std::string const &outFilename, std::unordered_map<KwargsKeys, bool> kwargs) {
        for (auto &[key, value] : defaultKwargs) {
            if (!kwargs.contains(key))
                kwargs[key] = defaultKwargs.at(key);
        }

        auto text = HuffmanIO::readFromFile(inFilename);
        if (text->empty())
            throw std::runtime_error("Cannot compress empty files");

        std::unordered_map<char, CharCodeWithMeta> codes = std::make_shared<HuffmanTree>(*text)->buildCodes();
        auto encoder = std::make_shared<HuffmanStringEncoder>(codes, *text);
        auto encodedText = encoder->getEncoded();

        HuffmanIO::writeToFile(outFilename, *encodedText);



        if (kwargs.at(KwargsKeys::print_codes))
            HuffmanIO::printCodes(codes);
        if (kwargs.at(KwargsKeys::print_stats))
            HuffmanIO::printStats(text->length(), encodedText->length());
        if (kwargs.at(KwargsKeys::save_stats))
            HuffmanIO::saveStats(text->length(), encodedText->length());
    }

    void Huffman::decompress(std::string const &inFilename, std::string const &outFilename) {
        auto encodedText = HuffmanIO::readFromFile(inFilename);
        auto text = std::make_shared<HuffmanStringDecoder>(*encodedText)->getDecoded();
        HuffmanIO::writeToFile(outFilename, *text);

        HuffmanIO::printStats(encodedText->length(), text->length());
    }
}