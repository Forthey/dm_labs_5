#include "Graph.h"

#include <memory>
#include <stack>
#include <stdexcept>
#include <unordered_set>

Cycle Graph::extractCycleFromPath(int vertex, Path const &path) {
    Cycle cycle;
    cycle.emplace_back(vertex);
    for (auto iter = ++path.rbegin(); iter != path.rend(); ++iter) {
        cycle.emplace_back(*iter);
        if (*iter == vertex) {
            return cycle;
        }
    }
    return {};
}

std::pair<ConnectivityComponents, Cycle> Graph::checkIfAcyclicAndConnected() {
    struct TraverseData {
        int const vertex; // Текущая вершина
        int const parent; // Родительская вершина, из которой мы попали в текущую
        Path path; // Путь до указанной вершины. Необходим для отображения цикла

        TraverseData(int vertex, int parent, Path &&pathBefore) : vertex(vertex), parent(parent), path(pathBefore) {
            path.emplace_back(vertex);
        }

        TraverseData(TraverseData &&data) noexcept : vertex(data.vertex), parent(data.parent),
                                                     path(std::move(data.path)) {
        }
    };

    // Двумерный массив, в котором будут храниться компоненты связности. Если их > 1, то граф несвязный
    ConnectivityComponents connectivityComponents;
    // connectivityComponents.emplace_back();

    // Цикл: список вершин
    Cycle cycle;

    if (vertices.empty()) {
        return {connectivityComponents, cycle};
    }

    // Стек для обхода в глубину
    std::stack<std::shared_ptr<TraverseData> > traverseStack;
    // Структура "множество" для отслеживания посещения
    std::unordered_set<int> nonVisitedVertices(vertices.size());
    for (int i = 0; i < vertices.size(); i++) {
        nonVisitedVertices.insert(i);
    }

    for (int i = 0; i < vertices.size(); i++) {
        std::unordered_set<int> adjVertices(vertices[i].size());
        for (int adjVertex : vertices[i]) {
            if (adjVertices.contains(adjVertex)) {
                cycle.emplace_back(adjVertex);
                cycle.emplace_back(i);
                cycle.emplace_back(adjVertex);
                i = vertices.size();
                break;
            }
            adjVertices.insert(adjVertex);
        }
    }

    // Этот цикл неявно обходит все компоненты связности
    while (!nonVisitedVertices.empty()) {
        // Добавляем ещё одну компоненту связности
        connectivityComponents.emplace_back();

        // DFS -- начинается каждый раз для каждой компоненты связности
        traverseStack.emplace(std::make_shared<TraverseData>(*nonVisitedVertices.begin(), -1, Path{}));
        while (!traverseStack.empty()) {
            auto data = traverseStack.top();
            traverseStack.pop();

            if (!nonVisitedVertices.contains(data->vertex)) {
                if (cycle.empty()) {
                    cycle = extractCycleFromPath(data->vertex, data->path);
                }
                continue;
            }
            // Добавляем вершину в последнюю компоненту связности
            connectivityComponents.back().emplace_back(data->vertex);
            // "Посещаем" вершину
            nonVisitedVertices.erase(data->vertex);

            // Проходим по смежным вершинам
            for (int adjVertex: vertices[data->vertex]) {
                // Если вершина родительская
                if (data->parent == adjVertex) {
                    continue;
                }
                traverseStack.emplace(std::make_shared<TraverseData>(adjVertex, data->vertex, std::move(data->path)));
            }
        }
    }

    return {connectivityComponents, cycle};
}

int Graph::countEdges() const {
    int edgesCnt = 0;
    for (int i = 0; i < vertices.size(); i++) {
        edgesCnt += static_cast<int>(vertices[i].size());
        // for (int j = 0; j < vertices[i].size(); j++) {
        //     if (vertices[i][j] >= i) {
        //         edgesCnt++;
        //     }
        // }
    }
    return edgesCnt / 2;
}


Graph::CheckResult Graph::checkTreeProperties() {
    auto [connectivityComponents, cycle] = checkIfAcyclicAndConnected();
    return {std::move(connectivityComponents), std::move(cycle), countEdges(), static_cast<int>(vertices.size())};
}
