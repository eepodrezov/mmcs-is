#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include "dfs.h"  
#include "bfs.h"  

using namespace std;
using Graph = vector<vector<int>>;

/**
 * Шаблонная функция для тестирования алгоритма поиска (DFS или BFS).
 *
 * @param graph Входной параметр - граф для тестирования.
 * @param expectedOutput Ожидаемый результат выполнения алгоритма.
 * @param algorithm Функция, которая реализует алгоритм поиска (DFS или BFS).
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
        { {{1, 2}, {0, 3, 4}, {0, 5}, {1}, {1}, {2}}, {0, 1, 3, 4, 2, 5} },
        { {{1}, {0}, {3}, {2}}, {0, 1} },
        { {{1, 2}, {0}, {0}}, {0, 1, 2} },
        { {{1, 3}, {0, 2}, {1}, {0}}, {0, 1, 2, 3} },
        { {{1, 4}, {0, 2, 3}, {1}, {1}, {0}}, {0, 1, 2, 3, 4} }
    };

    cout << "Тестирование DFS:" << endl;
    for (const auto& testCase : testCases) {
        searchAlgorithm(testCase.first, testCase.second, [](const Graph& graph, int startNode, vector<bool>& visited) {
            dfs(graph, startNode, visited);
        });
    }

    cout << "Тестирование BFS:" << endl;
    for (const auto& testCase : testCases) {
        searchAlgorithm(testCase.first, testCase.second, [](const Graph& graph, int startNode, vector<bool>& visited) {
            bfs(graph, startNode);  
        });
    }

    return 0;
}
