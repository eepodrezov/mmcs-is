#ifndef BFS_H
#define BFS_H

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
using Graph = vector<vector<int>>;

/**
 * Выполняет обход графа в ширину (BFS).
 *
 * @param graph Входной граф, представленный в виде матрицы смежности.
 * @param startNode Индекс узла, с которого начинается обход.
 */
void bfs(const Graph& graph, int startNode) {
    // Вектор для отслеживания посещенных узлов
    vector<bool> visited(graph.size(), false);
    // Очередь для хранения узлов для обработки
    queue<int> q;

    // Отмечаем начальный узел как посещенный и добавляем его в очередь
    visited[startNode] = true;
    q.push(startNode);

    // Пока очередь не пуста
    while (!q.empty()) {
        // Извлекаем узел из очереди
        int node = q.front();
        q.pop();
        cout << node << " ";  // Выводим узел

        // Обрабатываем соседей текущего узла
        for (int neighbor : graph[node]) {
            // Если сосед еще не был посещен, добавляем его в очередь
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

#endif