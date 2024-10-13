// Алгоритм поиска в глубину работает следующим образом:
// 1. Начните с того, что поместите любую вершину графа на вершину стека.
// 2. Возьмите верхний элемент стека и добавьте его в список “Пройденных”.
// 3. Создайте список смежных вершин для этой вершины. Добавьте те вершины, 
//которых нет в списке “Пройденных”, в верх стека.
// 4. Необходимо повторять шаги 2 и 3, пока стек не станет пустым.

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

// Объявление графа как списка смежности
using Graph = vector<vector<int>>;

/**
 * Функция для выполнения поиска в глубину (DFS) в графе.
 *
 * @param graph Входной параметр - граф, представленный в виде списка смежности.
 * @param node Текущая вершина, с которой начинается поиск.
 * @param visited Вектор, который отслеживает посещенные вершины.
 */
void dfs(const Graph& graph, int node, vector<bool>& visited) {
    // Помечаем текущую вершину как посещенную
    visited[node] = true;
    cout << node << " "; // Выводим текущую вершину

    // Рекурсивно вызываем dfs для всех соседей
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(graph, neighbor, visited);
        }
    }
}

#include <iomanip> 

/**
 * Функция для тестирования алгоритма поиска в глубину (DFS).
 *
 * @param graph Входной параметр - граф для тестирования.
 * @param expectedOutput Ожидаемый результат выполнения DFS.
 */
void testDFS(const Graph& graph, const vector<int>& expectedOutput) {
    // Начинаем замер времени выполнения
    auto start = chrono::high_resolution_clock::now();

    vector<bool> visited(graph.size(), false); // Вектор для отслеживания посещенных вершин
    cout << "Результат поиска в глубину: ";
    dfs(graph, 0, visited); // Запускаем поиск с вершины 0
    cout << endl;

    // Завершаем замер времени выполнения
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start; // Получаем время в миллисекундах

    // Проверка на соответствие ожидаемому результату
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
    // Массив из 5 объектов входных значений (графов) и ожидаемых результатов
    const vector<pair<Graph, vector<int>>> testCases = {
        { // Тест 1
            {{1, 2}, {0, 3, 4}, {0, 5}, {1}, {1}, {2}},
            {0, 1, 3, 4, 2, 5}
        },
        { // Тест 2
            {{1}, {0}, {3}, {2}},
            {0, 1}
        },
        { // Тест 3
            {{1, 2}, {0}, {0}},
            {0, 1, 2}
        },
        { // Тест 4
            {{1, 3}, {0, 2}, {1}, {0}},
            {0, 1, 2, 3}
        },
        { // Тест 5
            {{1, 4}, {0, 2, 3}, {1}, {1}, {0}},
            {0, 1, 2, 3, 4}
        }
    };

    // Прогон функции тестирования по массиву
    for (const auto& testCase : testCases) {
        testDFS(testCase.first, testCase.second);
    }

    return 0;
}
