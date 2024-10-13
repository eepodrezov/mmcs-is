#ifndef DFS_H
#define DFS_H

#include <iostream>
#include <vector>

using namespace std;
using Graph = vector<vector<int>>;

/**
 * Выполняет обход графа в глубину (DFS).
 *
 * @param graph Входной граф, представленный в виде матрицы смежности.
 * @param node Индекс узла, с которого начинается обход.
 * @param visited Вектор для отслеживания посещенных узлов.
 */
void dfs(const Graph& graph, int node, vector<bool>& visited) {
    // Отмечаем узел как посещенный
    visited[node] = true;
    cout << node << " ";  // Выводим узел

    // Рекурсивно обрабатываем всех соседей текущего узла
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(graph, neighbor, visited);
        }
    }
}

#endif
