#pragma once
#include <fstream>
#include <format>

#include "Huffman.h"

using Keys = Huffman::Huffman::KwargsKeys;

class Tester {
public:
    static void createTestFiles(int begin, int number, int step) {
        for (int i = 0, currentCharNumber = begin; i < number; i++, currentCharNumber += step) {
            std::ifstream orwell("examples/orwell.txt");
            std::ofstream f(std::format("examples/tests/test_{}.txt", std::to_string(i)));

            std::string s(currentCharNumber, 'a');
            orwell.read(&s[0], currentCharNumber);
            f << s;
            orwell.close();
            f.close();
        }
    }

    static void doTest(int begin, int number, int step) {
        for (int i = 0, currentCharNumber = begin; i < number; i++, currentCharNumber += step) {
            Huffman::Huffman::compress(std::format("examples/tests/test_{}.txt", std::to_string(i)),
                                       "examples/out.huff", {{Keys::save_stats, true}});
        }
    }
};