#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include "a_star.h"  
#include "bfs.h"
#include "dfs.h"

using namespace std;
using Graph = vector<vector<int>>;

/**
 * Шаблонная функция для тестирования алгоритма поиска (DFS, BFS или A*).
 *
 * @param graph Входной параметр - граф для тестирования.
 * @param expectedOutput Ожидаемый результат выполнения алгоритма.
 * @param algorithm Функция, которая реализует алгоритм поиска (DFS, BFS или A*).
 */
template <typename Func>
void searchAlgorithm(const Graph& graph, const vector<int>& expectedOutput, Func algorithm) {
    auto start = chrono::high_resolution_clock::now();

    vector<bool> visited(graph.size(), false);

    cout << "Результат работы алгоритма: ";
    algorithm(graph, 0, visited);
    cout << endl;

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;

    // Проверка на соответствие ожидаемому результату (простой вариант)
    bool testPassed = true;
    for (int expectedNode : expectedOutput) {
        if (!visited[expectedNode]) {
            testPassed = false;
            break;
        }
    }

    // Вывод результата теста
    cout << (testPassed ? "Тест пройден" : "Тест не пройден") << endl;

    // Вывод времени выполнения в миллисекундах с округлением до 2 знаков после запятой
    cout << "Время выполнения: " << fixed << setprecision(4) << duration.count() << " мс." << endl;
    cout << "----------------------------------------" << endl;
}

int main() {
    const vector<pair<Graph, vector<int>>> testCases = {
        { {{0, 0, 1, 0, 0}, {0, 0, 1, 0, 0}, {1, 0, 0, 1, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 0, 0}}, {0, 1, 2, 6, 10} },
        { {{0, 1, 0}, {0, 0, 0}, {0, 1, 0}}, {0, 3, 4, 1, 2} },
        { {{0, 0, 1, 1}, {1, 0, 1, 0}, {0, 0, 0, 1}, {1, 1, 0, 0}}, {0, 1, 4, 7, 8, 9, 5, 2, 6, 3} },
    };

    cout << "Тестирование A*:" << endl;
    for (const auto& testCase : testCases) {
        searchAlgorithm(testCase.first, testCase.second, [](const Graph& graph, int startIdx, vector<bool>& visited) {
            // Создаем начальную и целевую ноды с уникальными именами
            Node startNode(0, 0);  // Начальная нода
            Node goalNode(graph.size() - 1, graph[0].size() - 1);  // Целевая нода, например, нижний правый угол

            // Вызов функции A*
            a_star(graph, startNode, goalNode);
        });
    }

    return 0;
}
