#include "CLI.h"

#include <iostream>
#include <format>
#include <memory>

#include "GraphIO.h"

std::string const CLI::testFolder = "examples";

void CLI::run() {
    while (true) {
        std::cout << "Enter test name (\"exit\" to quit):";
        std::string command;
        std::cin >> command;

        if (command == "exit") {
            break;
        }

        std::shared_ptr<Graph> graph;
        std::string path;
        path = std::format("{}/{}", testFolder, command);
        graph = GraphIO::readFromFile(path);
        if (graph == nullptr) {
            std::cout << "Graph could not be read\n";
            continue;
        }
        auto [largestSet, minCoverage] = graph->findLargestIndependentSetAndSmallestCoverage();
        GraphIO::writeToFile(path, largestSet, minCoverage);
    }
}
