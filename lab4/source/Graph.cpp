#include "Graph.h"

#include <stack>
#include <unordered_set>
#include <generator>
#include <memory>
#include <memory>
#include <memory>


/**
 * Функция вычитает из одного множества другое
 * Сложность O(set.size() + toRemove.size()) = O(V)
 * @param set Уменьшаемое множество
 * @param toRemove Вычитаемое множество
 * @return Результат
 */
Set operator-(Set const &set, Vertices const &toRemove) {
    Set result;
    for (int v: set) {
        result.insert(v);
    }
    for (int v: toRemove) {
        result.erase(v);
    }
    return result;
}

Set operator-(Set const &set, int v) {
    return set - Vertices(1, v);
}


/**
 * Функция проверяет, останется ли множество независимым после добавления вершины.
 * Сложность функции O(V)
 * @param set Независимое множества
 * @param v Вершина, которую хочется добавить
 * @return Останется ли множество независимым
 */
bool Graph::isStillIndependent(Set const &set, int v) const {
    std::unordered_set<int> adjVertices;
    for (int adjVertex: this->vertices[v]) {
        adjVertices.insert(adjVertex);
    }

    for (int u: set) {
        if (adjVertices.contains(u)) {
            return false;
        }
    }
    return true;
}

/**
 * Функция ищет наибольшее независимое множество путём перебора всех возможных независимых множеств
 * Сложность функции O(V * 2^V):
 *      - В цикл for перебора оставшихся вершин внутри while алгоритм зайдет в худшем случае 2^V раз - так как в худшем случае придётся перебрать всевозможные комбинации множества вершин
 *      - В цикле for последовательно вызываются функции isStillIndependent и operator-, каждая из которых имеет сложность O(V)
 * @param result
 * @param graphVertices
 */
void Graph::traverse(Set &result, Set &graphVertices) const {
    struct TraverseData {
        Set currentIndependentSet;
        Set remainingVertices;

        TraverseData(Set &&currentIndependentSet, Set &&remainingVertices)
            : currentIndependentSet(currentIndependentSet), remainingVertices(remainingVertices) {}

        explicit TraverseData(Set &&remainingVertices) : remainingVertices(remainingVertices) {}
    };

    std::stack<std::shared_ptr<TraverseData>> traverseStack;

    traverseStack.emplace(std::make_shared<TraverseData>(std::move(graphVertices)));

    int count = 0;

    while (!traverseStack.empty()) {
        auto data = traverseStack.top();
        traverseStack.pop();

        if (data->currentIndependentSet.size() > result.size()) {
            result = std::move(data->currentIndependentSet);
        }

        for (int v : data->remainingVertices) {
            count++;
            if (isStillIndependent(data->currentIndependentSet, v)) {
                Set expandedSet = std::move(data->currentIndependentSet);
                expandedSet.insert(v);

                traverseStack.emplace(std::make_shared<TraverseData>(
                    std::move(expandedSet),
                    std::move(data->remainingVertices - v - this->vertices[v])
                ));
            }
        }
    }

}

/**
 * Функция находит наибольшее независимое множество
 * Сложность O(V + V * 2^V) = O(V * 2^V)
 * @return Наибольшее независимое множества и наименьшее покрытие графа
 */
std::pair<Set, Set> Graph::findLargestIndependentSetAndSmallestCoverage() const {
    Set largestSet, minCoverage;

    Set graphVertices(this->vertices.size());
    for (int i = 0; i < this->vertices.size(); i++) {
        graphVertices.insert(i);
    }

    traverse(largestSet, graphVertices);

    minCoverage.reserve(this->vertices.size() - largestSet.size());

    for (int vertex: graphVertices) {
        if (!largestSet.contains(vertex)) {
            minCoverage.insert(vertex);
        }
    }

    return {largestSet, minCoverage};
}
