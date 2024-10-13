#ifndef DFS_H
#define DFS_H

#include <iostream>
#include <vector>

using namespace std;
using Graph = vector<vector<int>>;

// Обход графа в глубину
void dfs(const Graph& graph, int node, vector<bool>& visited) {
    visited[node] = true;
    cout << node << " ";

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(graph, neighbor, visited);
        }
    }
}

#endif
