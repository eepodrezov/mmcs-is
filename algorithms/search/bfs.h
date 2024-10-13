#ifndef BFS_H
#define BFS_H

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
using Graph = vector<vector<int>>;

//Обход графа в ширину
void bfs(const Graph& graph, int startNode) {
    vector<bool> visited(graph.size(), false);
    queue<int> q;

    visited[startNode] = true;
    q.push(startNode);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

#endif
