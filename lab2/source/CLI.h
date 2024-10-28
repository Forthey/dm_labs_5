#pragma once
#include <format>

#include "GraphIO.h"

class CLI {
public:
    static void startInteraction() {
        while (true) {
            std::string filename;
            std::cout << "Graph filename (or \":q\" to quit)\n> ";
            std::cin >> filename;

            if (filename == ":q") {
                break;
            }

            std::string const path = std::format("examples/{}.bigraph", filename);
            auto const result = GraphIO::readGraphFromFile(path);
            if (result == nullptr) {
                std::cout << std::format("Failed to read file \"{}\"\n", path);
                continue;
            }

            auto const match = result->findLargestMatch();

            GraphIO::writeResultToFile(std::format("examples/{}.match", filename), *match);

            std::cout << std::format("Largest match size: {}\n", match->size());
            for (auto &[left, right]: *match) {
                std::cout << std::format("\t{} - {}\n", left, right);
            }

        }
    }
};
