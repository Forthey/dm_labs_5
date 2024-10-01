#include <iostream>
#include <format>
#include <vector>

#include "Huffman.h"
#include "Tester.h"
#include "CLI.h"
#include "ArgsParser.h"

int main(int argc, char* argv[]) {
    try {
        if (argc > 1) {
            ArgsParser::parseArgs(argc, argv);
        } else {
            CLI::startInteraction();
        }
    }
    catch (std::exception &exception) {
        std::cout << exception.what() << std::endl;
        return 1;
    }
//    Tester::createTestFiles(10, 100, 100);
//    Tester::doTest(10, 100, 100);
    return 0;
}