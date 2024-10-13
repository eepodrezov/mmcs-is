#ifndef A_STAR_H
#define A_STAR_H

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>

using namespace std;

struct Node {
    int x, y;               // Координаты в графе (или позиция узла)
    int gCost;              // Стоимость пути от начальной точки
    int hCost;              // Эвристическая стоимость до цели (Манхэттенское расстояние)
    int fCost() const { return gCost + hCost; } // Суммарная стоимость (f = g + h)
    Node* parent;           // Родительский узел для восстановления пути

    Node(int x, int y, int gCost = 0, int hCost = 0, Node* parent = nullptr)
        : x(x), y(y), gCost(gCost), hCost(hCost), parent(parent) {}
};

// Эвристическая функция Манхэттенского расстояния
int manhattanDistance(const Node& a, const Node& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

// Алгоритм A* с эвристикой Манхэттенского расстояния
void a_star(const vector<vector<int>>& graph, const Node& startNode, const Node& goalNode) {
    int rows = graph.size();
    int cols = graph[0].size();

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> openList;

    Node* start = new Node(startNode.x, startNode.y, 0, manhattanDistance(startNode, goalNode));
    openList.push({start->fCost(), start});

    while (!openList.empty()) {
        Node* current = openList.top().second;
        openList.pop();

        if (current->x == goalNode.x && current->y == goalNode.y) {
            // Достигли цели, восстановим путь
            cout << "Путь: ";
            Node* pathNode = current;
            while (pathNode != nullptr) {
                cout << "(" << pathNode->x << ", " << pathNode->y << ") ";
                pathNode = pathNode->parent;
            }
            cout << endl;
            return;
        }

        if (visited[current->x][current->y]) {
            continue;
        }

        visited[current->x][current->y] = true;

        // Проверяем соседей
        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // Вверх, вниз, влево, вправо
        for (auto& direction : directions) {
            int newX = current->x + direction.first;
            int newY = current->y + direction.second;

            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && !visited[newX][newY] && graph[newX][newY] != 1) {
                int newGCost = current->gCost + 1; // Вес пути к соседнему узлу (в данном случае 1)
                int newHCost = manhattanDistance(Node(newX, newY), goalNode);
                Node* neighbor = new Node(newX, newY, newGCost, newHCost, current);

                openList.push({neighbor->fCost(), neighbor});
            }
        }
    }

    cout << "Путь не найден!" << endl;
}

#endif // A_STAR_H
