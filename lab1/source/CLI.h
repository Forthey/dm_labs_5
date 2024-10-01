#pragma once
#include <iostream>

#include "Huffman.h"

using Keys = Huffman::Huffman::KwargsKeys;

class CLI {
public:
    static void startInteraction() {
        char choice;

        std::cout << "Compress/Decompress? (c/d): ";
        std::cin >> choice;

        std::string inFilepath, outFilepath;

        std::cout << "file path: ";
        std::cin >> inFilepath;

        std::cout << "out file path: ";
        std::cin >> outFilepath;

        if (choice == 'c') {
            char printCodes, printStats;

            std::cout << "Print codes? (y/n): ";
            std::cin >> printCodes;

            std::cout << "Print stats? (y/n): ";
            std::cin >> printStats;

            Huffman::Huffman::compress(inFilepath, outFilepath, {
                {Keys::print_codes, printCodes == 'y'},
                {Keys::print_stats, printStats != 'n'}
            });
        }
        else {
            Huffman::Huffman::decompress(inFilepath, outFilepath);
        }

        std::cout << std::format("The result was saved into {}\n", outFilepath);
    }
};
