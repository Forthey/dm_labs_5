#pragma once
#include <string>
#include <unordered_map>

#include "Graph.h"

class CLI {
    static std::unordered_map<std::string, std::string> const tagToFolder;
    static std::string const testFolder;

    static std::string resultToString(Graph::CheckResult const &result);

    static std::string argsToPath(std::vector<std::string> const &args);

public:
    static void run();
};
