#include "CLI.h"

#include <iostream>
#include <format>
#include <memory>

#include "GraphIO.h"

std::unordered_map<std::string, std::string> const CLI::tagToFolder = {
    {"ca", "connected_acyclic"},
    {"cc", "connected_cyclic"},
    {"da", "disconnected_acyclic"},
    {"dc", "disconnected_cyclic"}
};

std::string const CLI::testFolder = "examples";

std::string CLI::resultToString(Graph::CheckResult const &result) {
    std::string connectivityStr = "Связный: ", cycleStr = "Ацикличный: ", treeLikeStr = "Древочисленный: ";

    if (result.connectivity_components.size() == 1) {
        connectivityStr += "да\n";
    } else {
        connectivityStr += "нет\n\tКомпоненты связности:\n";
        for (auto const &connectivity_component: result.connectivity_components) {
            connectivityStr += "\t\t - ";
            for (int j = 0; j < connectivity_component.size(); j++) {
                connectivityStr += std::to_string(connectivity_component[j] + 1);
                if (j < connectivity_component.size() - 1) {
                    connectivityStr += ", ";
                }
            }
            connectivityStr += "\n";
        }
    }

    if (result.cycle.empty()) {
        cycleStr += "да\n";
    } else {
        cycleStr += "нет\n\tЦикл: ";
        for (int i = 0; i < result.cycle.size(); ++i) {
            cycleStr += std::to_string(result.cycle[i] + 1);
            if (i < result.cycle.size() - 1) {
                cycleStr += " -> ";
            }
        }
        cycleStr += "\n";
    }

    if (result.edgeCnt == result.vertexCnt - 1) {
        treeLikeStr += "да\n";
    } else {
        treeLikeStr += std::format("нет\n\tКоличество вершин: {}, количество рёбер: {}\n", result.vertexCnt,
                                   result.edgeCnt);
    }

    return connectivityStr + cycleStr + treeLikeStr;
}

std::string CLI::argsToPath(std::vector<std::string> const &args) {
    if (args.size() != 2 || !tagToFolder.contains(args[0])) {
        return "";
    }
    return std::format("{}/{}/{}", testFolder, tagToFolder.at(args[0]), args[1]);
}

void CLI::run() {
    std::cout << "Test tags:\n"
            "\tca - connected and acyclic examples\n"
            "\tcc - connected and cyclic examples\n"
            "\tda - disconnected and acyclic examples\n"
            "\tdc - disconnected and cyclic examples\n"
            "\trd - random graph\n";

    while (true) {
        std::cout << "Enter test tag and test name separated by space (\"exit\" to quit):";
        std::string command;
        std::cin >> command;

        if (command == "exit") {
            break;
        }

        std::shared_ptr<Graph> graph;
        std::string path;
        if (command == "rd") {
            int vertexCount, edgeCount;
            if (!(std::cin >> vertexCount >> edgeCount)) {
                std::cout << "Invalid input\n";
                std::cin.clear();
                continue;
            }
            graph = GraphIO::createRandomGraph(vertexCount, edgeCount);
        } else {
            std::string testNum;
            if (!(std::cin >> testNum) || !tagToFolder.contains(command)) {
                std::cout << "Invalid input\n";
                std::cin.clear();
                continue;
            }
            path = std::format("{}/{}/{}", testFolder, tagToFolder.at(command), testNum);
            graph = GraphIO::readFromFile(path);
        }
        if (graph == nullptr) {
            std::cout << "Graph could not be read\n";
            continue;
        }
        Graph::CheckResult result = graph->checkTreeProperties();
        auto resultString = resultToString(result);
        std::cout << resultString << '\n';

        if (!path.empty())
            if (!GraphIO::writeToFile(path, resultToString(result))) {
                std::cout << "Result could not be written\n";
            }
    }
}
